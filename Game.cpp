#include "Game.h"
#include "SDL2/SDL.h"
#include "MathAddon.h"
#include <iostream>


//in fullscren mode thew black bar is added in lower beacuse the screen is in 1920*1080 the tile is not fitted in that area // so solutiopn is add one plus 
Game::Game(SDL_Window* window, SDL_Renderer* renderer, int windowWidth, int windowHeight) :
    placementModeCurrent(PlacementMode :: tile),
    level(renderer,windowWidth/tileSize + (windowWidth % tileSize > 0), windowHeight / tileSize + (windowHeight % tileSize > 0)) {
    //Run the game.
    if (window != nullptr && renderer != nullptr) {
      //  listPlants.push_back(Plant(renderer, Vector2D(5.5f, 3.5f)));

         //Initializ a texture that will 
        textureShadows = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_TARGET, windowWidth, windowHeight);
        SDL_SetTextureBlendMode(textureShadows, SDL_BLENDMODE_BLEND);
        SDL_SetTextureAlphaMod(textureShadows, (int)round(255 * 0.60f));

         Run(renderer);
    }
    
}


Game::~Game() {
    //Clean up.
    if (textureShadows != nullptr)
    {
        SDL_DestroyTexture(textureShadows);
        textureShadows = nullptr;
    }

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

        processEvents(sdl,running);
        update(dT);
        draw(sdl);
    }
}



void Game::processEvents(SDL_Renderer* renderer,bool& running) {
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
            {
                int tuleTypeID = event.key.keysym.scancode - SDL_SCANCODE_1;
                level.setTileTypeIDSelected(tuleTypeID);
                placementModeCurrent = PlacementMode::tile;
            }
				break;
            case SDL_SCANCODE_Q :
                setPlantTypeIDSelected(0);
                break;
            case SDL_SCANCODE_W:
                setPlantTypeIDSelected(1);
                break;
            case SDL_SCANCODE_E:
                setPlantTypeIDSelected(2);
                break;
            case SDL_SCANCODE_R:
                setPlantTypeIDSelected(3);
                break;
            case SDL_SCANCODE_T:
                setPlantTypeIDSelected(4);
                break;

                //select Animal

            case SDL_SCANCODE_A:
                setAnimalTypeIDSelected(0);
                break;
            case SDL_SCANCODE_S:
                setAnimalTypeIDSelected(1);
                break;
            case SDL_SCANCODE_D:
                setAnimalTypeIDSelected(2);
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
        //the mouse was pressed
        switch (mouseDownStatus) {
        case SDL_BUTTON_LEFT:
            switch (placementModeCurrent)
            {
            case  PlacementMode::tile:
                level.placeTileTypeIDSelected((int)posMouse.x, (int)posMouse.y);
                removePlantsIfTilesChanges();
                removeAnimalsIfTilesChanges();
                break;

            case PlacementMode::plants: addPlants(renderer, posMouse);
                break;

            case PlacementMode::animals : 
             //   if (mouseDownThisFrame) {
                    addAnimal(renderer, posMouse);
                    break;
             //   }
            }


            break;

        case SDL_BUTTON_RIGHT :
            removePlantsAtMousePosition(posMouse);
            removeAnimalAtMousePos(posMouse);
            break;
        } 
       
       
    
        //The mouse was pressed.
    }


}



void Game::update(float dT) {

    for (auto& plantSelected : listPlants)
        plantSelected.update(dT);

    for (auto& animalSelected : listAnimals)
        animalSelected.update(dT,*this);


}

void Game::draw(SDL_Renderer* renderer) {
    //Draw.
    //Set the background color.
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); //first set the bg 
    //Clear the screen.
    SDL_RenderClear(renderer); //clear the bg

   //Layer 1
    level.Draw(renderer, tileSize); //draw the level according to window height and widht


    //Layer 2  - Shadows
    SDL_SetRenderTarget(renderer, textureShadows); //Changes the drawing destination from the screen to your custom texture (textureShadows). , 
    //Now everything you draw will be drawn ONTO this texture instead of directly onto the screen. //creating a layer and draw on that layer

  
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0); //Clears the textureShadows so you can draw fresh shadows onto it without leftovers from the last frame
    SDL_RenderClear(renderer);//clear

    level.drawShadows(renderer, tileSize); //draw tile shadown on new layer 2

    for (auto& plantSelected : listPlants) //layer 2
        plantSelected.drawShadow(renderer, tileSize); //draw the plant shaows

    for (auto& animalSelected : listAnimals) //layer 2
        animalSelected.drawShadow(renderer, tileSize); //draw the plant shaows

    //set the render target back to window.
    SDL_SetRenderTarget(renderer, NULL); //set target back to layer 1 screen and 

    SDL_RenderCopy(renderer, textureShadows, NULL, NULL);//Draws the shadow texture onto the screen. ,It blends the shadows.

    

   
//Draw the plants.
    for (auto& plantSelected : listPlants) //layer 1 Draws the visible plants on layer 1
        plantSelected.Draw(renderer, tileSize);

    for (auto& animalSelected : listAnimals) //layer 2
        animalSelected.draw(renderer, tileSize); //draw the plant shaows

    //Send the image to the window.
    SDL_RenderPresent(renderer); //Actually displays everything you drew this frame onto the window.
    //Until this call, everything was just being prepared in memory(the backbuffer).



}

void Game::setPlantTypeIDSelected(int setTypeIDSelected)
{
    std::cout << setTypeIDSelected;
    plantTypeIDSelected = setTypeIDSelected;
    placementModeCurrent = PlacementMode::plants;
}


void Game::setAnimalTypeIDSelected(int setAnimalTypeID)
{
    animalTypeIDSelected = setAnimalTypeID;
    placementModeCurrent = PlacementMode::animals;

}



void Game::addPlants(SDL_Renderer* renderer, Vector2D posMouse)
{


      // std::cout << "plant";
    //if (Plant::checkIfTilesUnderOkForType((int)posMouse.x, (int)posMouse.y, plantTypeIDSelected, level))
    //{
    //    bool foundPlant = false;

    //    for (auto it = listPlants.begin(); it != listPlants.end() && foundPlant == false; it++) 
    //    {
    //        //  std::cout << "loopStart" << "\n";

    //         // Vector2D currentPos = posMouse;//(*it).getPos();
    //         //float x = currentPos.x;
    //         //float y = currentPos.y;
    //         //std::cout << x << " " << y << "\n";

    //        if ((*it).checkOverlapWithPlantTypeID((int)posMouse.x, (int)posMouse.y, plantTypeIDSelected))
    //        {
    //            foundPlant = true;
    //            //  std::cout << foundPlant;
    //             // break;
    //        }
    //    }

       // if (foundPlant == false) {
          //  std::cout << foundPlant;
            float randOffsetX = (MathAddon::randFloat() * 2.0f - 1.0f) * 0.1f;
            float randOffsetY = (MathAddon::randFloat() * 2.0f - 1.0f) * 0.1f;
            Vector2D pos((int)posMouse.x + 0.5f + randOffsetX, (int)posMouse.y + 0.5f + randOffsetY);

            if (Plant::checkIfPositionOkForType(pos, plantTypeIDSelected, *this)) {
               listPlants.push_back(Plant(renderer, plantTypeIDSelected, pos));

            }
            // std::cout << plantTypeIDSelected << "new" <<"\n";
      //  }
   // }

   

}

void Game::addAnimal(SDL_Renderer* renderer, Vector2D posMouse)
{
    if (Animal::checkIfPositionOkforType(posMouse, animalTypeIDSelected, *this)) {
      listAnimals.push_back(Animal(renderer, animalTypeIDSelected, posMouse, MathAddon::randAngleRad()));

    }
}

void Game::removePlantsAtMousePosition(Vector2D posMouse) {

    for (auto it = listPlants.begin(); it != listPlants.end();) {
        std::cout << "loopStart" << "\n";

        if ((*it).checkOverlapWithMouse((int)posMouse.x , (int)posMouse.y)) {
            it = listPlants.erase(it);
            
        }
        else {
            it++;
        }
    }
}

void Game::removePlantsIfTilesChanges()
{
    for (auto it = listPlants.begin(); it != listPlants.end();) {
        if ((*it).checkIfTilesUnderOk(level) == false) {
            it = listPlants.erase(it);
        }
        else {
            it++;
        }
    }
}

void Game::removeAnimalsIfTilesChanges()
{
    for (auto it = listAnimals.begin(); it != listAnimals.end();) {
        //std::cout << "loopStart" << "\n";

        if ((*it).checkIfTileUnderOk(level) == false) {
            it = listAnimals.erase(it);
        }
        else {
            it++;
        }
    }

}

void Game::removeAnimalAtMousePos(Vector2D posMouse)
{
    for (auto it = listAnimals.begin(); it != listAnimals.end();) {
        //std::cout << "loopStart" << "\n";

        if ((*it).checkCircleOverlap(posMouse , 0.0f)) {
            it = listAnimals.erase(it);
        }
        else {
            it++;
        }
    }
}


