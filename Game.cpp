#include "Game.h"
#include "SDL2/SDL.h"


//in fullscren mode thew black bar is added in lower beacuse the screen is in 1920*1080 the tile is not fitted in that area // so solutiopn is add one plus 
Game::Game(SDL_Window* window, SDL_Renderer* renderer, int windowWidth, int windowHeight) : level(renderer,windowWidth/tileSize + (windowWidth % tileSize > 0), windowHeight / tileSize + (windowHeight % tileSize > 0)) {
    //Run the game.
    if (window != nullptr && renderer != nullptr) {
       
          Run(renderer);
        }
    
}


Game::~Game() {
    //Clean up.
    TextureLoader::deallocateTextures();
}

void Game::Run(SDL_Renderer * sdl)
{
    //Store the current times for the clock.
    auto time1 = std::chrono::system_clock::now();
    auto time2 = std::chrono::system_clock::now();


    //Start the game loop and run until it's time to stop.
    bool running = true;
    while (running) {
        //Determine how much time has elapsed since the last frame.
        time2 = std::chrono::system_clock::now();
        std::chrono::duration<float> timeDelta = time2 - time1;
        float timeDeltaFloat = timeDelta.count();

        //Store the new time for the next frame.
        time1 = time2;

        //The amount of time for each frame (no longer than 20 fps).
        const float dT = std::min(timeDeltaFloat, 1.0f / 20.0f);

        processEvents(running);
        update(dT);
        draw(sdl);
    }
}



void Game::processEvents(bool& running) {
    bool mouseDownThisFrame = false;

    //Process events.
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            running = false;
            break;

        case SDL_MOUSEBUTTONDOWN:
            mouseDownThisFrame = (mouseDownStatus == 0);
            if (event.button.button == SDL_BUTTON_LEFT)
                mouseDownStatus = SDL_BUTTON_LEFT;
            else if (event.button.button == SDL_BUTTON_RIGHT)
                mouseDownStatus = SDL_BUTTON_RIGHT;
            break;
        case SDL_MOUSEBUTTONUP:
            mouseDownStatus = 0;
            break;

        case SDL_KEYDOWN:
            switch (event.key.keysym.scancode) {
                //Quit the game.
            case SDL_SCANCODE_ESCAPE:
                running = false;
                break;

			case SDL_SCANCODE_1:
			case SDL_SCANCODE_2:
			case SDL_SCANCODE_3:
			case SDL_SCANCODE_4:
			case SDL_SCANCODE_5:
			case SDL_SCANCODE_6:
			case SDL_SCANCODE_7:
				int tuleTypeID = event.key.keysym.scancode - SDL_SCANCODE_1;
				level.setTileTypeIDSelected(tuleTypeID);
				break;
            }
        }
    }


    //Process input from the mouse cursor.
    int mouseX = 0, mouseY = 0;
    SDL_GetMouseState(&mouseX, &mouseY);
    //Convert from the window's coordinate system to the game's coordinate system.
    Vector2D posMouse((float)mouseX / tileSize, (float)mouseY / tileSize);

    if (mouseDownStatus > 0) {

        if (mouseDownStatus == SDL_BUTTON_LEFT) {
			level.placeTileTypeIDSelected((int)posMouse.x, (int)posMouse.y);
        }
        //The mouse was pressed.
    }
}



void Game::update(float dT) {

}



void Game::draw(SDL_Renderer* renderer) {
    //Draw.
    //Set the background color.
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    //Clear the screen.
    SDL_RenderClear(renderer);

   
    level.Draw(renderer, tileSize);


    //Send the image to the window.
    SDL_RenderPresent(renderer);
}