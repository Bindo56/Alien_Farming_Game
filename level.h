#pragma once
#include  <Vector>
#include "SDL2/SDL.h"
#include  "Tile.h"
class level
{
public :
	level(SDL_Renderer* renderer,int setTileCountX, int setTileCountY);
	void Draw(SDL_Renderer* render, int tilesize);
	void setTileTypeIDSelected(int setTileTypeSelected);
	void placeTileTypeIDSelected(int x, int y);

private:
	
	std::vector<Tile> listTiles; //store the array count of tile
	const int tileCountX, tileCountY;

	int TileTypeIDSelected = 0;
};

