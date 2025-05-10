#pragma once

#include "SDL2\SDL.h"
#include "Vector2D.h"
#include <vector>
#include <iostream>
class Tile
{

private: 
	struct Type //Typr data
	{
		std::string name;
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

	int typeID;
	bool isWet = false; //is the tile wet or not

	static void refreshSurroundingIsWet(int x, int  y, std::vector<Tile>& listTile, int TileCountX, int tileCountY);
	static const std::vector<Type> listTileTypes;
	bool checkIfOkForPlant(bool growsOnWetDirt);
	bool CheckIfOkForAnimal(int x, int y,Vector2D posCheck, float radiusCircle);
	bool CheckCircleOverlap(int x, int y, Vector2D posCheck, float radiusCheck);




private:

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

