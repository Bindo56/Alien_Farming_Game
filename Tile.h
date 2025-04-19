#pragma once

#include "SDL2\SDL.h"
#include <vector>
class Tile
{

private: 
	struct Type //Typr data
	{
		int height;
		SDL_Color corlorDark = {};
		SDL_Color corlorLight = {};
	};

public:
	  Tile(SDL_Renderer* renderer);  //declare constructor in public 

	void drawTile(SDL_Renderer* render,int x,int y, int tilesize);

	void drawShadow(SDL_Renderer* renderer, int x, int y, int tileSize,
		std::vector<Tile>& listTile, int TileCountX, int TileCountY);


	void setTypeID(int id);// { typeID = id; } //set the type of tile
	static const std::vector<Type> listTileTypes;


private:
	int typeID;
	bool isTileHigher(int x, int y, std::vector<Tile>& listTile, int TileCountX, int tileCountY);

	static std::vector<SDL_Texture*> listTextureTileShadow;
	
	//SDL_Texture* textureTileShadow = nullptr,
	//	* textureTileShadowRight = nullptr,
	//	* textureTileShadowBottom = nullptr,
	//	* textureTileShadowLeft = nullptr,

	//	* textureTileShadowTopLeft = nullptr,
	//	* textureTileShadowTopRight = nullptr,
	//	* textureTileShadowBottomLeft = nullptr,
	//	* textureTileShadowBottomRight = nullptr;


};

