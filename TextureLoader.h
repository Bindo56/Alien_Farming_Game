#pragma once
#include <string>
#include <unordered_map>
#include "SDL2/SDL.h"



class TextureLoader
{
public:
	static SDL_Texture* loadTexture(SDL_Renderer* renderer, std::string filename);
	static void deallocateTextures();


private:
	static std::unordered_map<std::string, SDL_Texture*> umapTexturesLoaded;
};