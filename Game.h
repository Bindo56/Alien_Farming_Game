#pragma once
#include <chrono>
#include "SDL2/SDL.h"
#include "TextureLoader.h"
#include "Vector2D.h"
#include "level.h"
#



class Game
{
public:
	Game(SDL_Window* window, SDL_Renderer* renderer, int windowWidth, int windowHeight);
	~Game();
	void Run(SDL_Renderer* sdl);


private:
	void processEvents(bool& running);
	void update(float dT);
	void draw(SDL_Renderer* renderer);

	int mouseDownStatus = 0;
	const int tileSize = 64;
	level level;  //initilize this construtor//Since level is a member object of class Game, it must be constructed when the Game object is constructed.//excution order 

};