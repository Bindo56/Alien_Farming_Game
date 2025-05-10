#pragma once
#include  <Vector>
#include  "Vector2D.h"
#include "SDL2/SDL.h"
#include  "Tile.h"
class level
{
public :
	level(SDL_Renderer* renderer,int setTileCountX, int setTileCountY);
	void Draw(SDL_Renderer* render, int tilesize);
	void setTileTypeIDSelected(int setTileTypeSelected);
	void placeTileTypeIDSelected(int x, int y);
	void drawShadows(SDL_Renderer* renderer , int tileSize);
	bool checkIfTileOkForPlant(int x, int y, bool growsOnWetDirt);
	bool checkIfTileOkForAnimal(Vector2D posCheck, float radiusCheck);

private:
	
	std::vector<Tile> listTiles; //store the array count of tile
	const int tileCountX, tileCountY;

	int TileTypeIDSelected = 0;
};

