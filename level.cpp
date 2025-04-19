#include "level.h"
#include <iostream>
//#include "SDL2/SDL.h"

level::level(SDL_Renderer* renderer,int setTileCountX, int setTileCountY) :
	tileCountX(setTileCountX), tileCountY(setTileCountY)
{
	std::cout << tileCountX << '\n';
	std::cout << tileCountY << '\n';

	size_t listTilesize = (size_t)tileCountX * tileCountY;
	listTiles.assign(listTilesize, Tile(renderer));

	

}

void level::Draw(SDL_Renderer* render, int tilesize)
{
	for (int y = 0; y < tileCountY; y++)
	{
		for (int x = 0; x < tileCountX; x++)
		{
			int index = x + y * tileCountX;

			listTiles[index].drawTile(render, x, y, tilesize);
			listTiles[index].drawShadow(render, x, y, tilesize, listTiles, tileCountX, tileCountY);
			
		}
	}

	
}

void level::setTileTypeIDSelected(int setTileTypeSelected)
{
	if (setTileTypeSelected > -1 && setTileTypeSelected <= Tile::listTileTypes.size()) {
		TileTypeIDSelected = setTileTypeSelected;
	}
	else {
		std::cout << "Error: Invalid tile type selected." << std::endl;
	}
}

void level::placeTileTypeIDSelected(int x, int y)
{
	int index = x + y * tileCountX;
	if (index >= 0 && index < listTiles.size()&& x > -1 && x < tileCountX && y > -1 && y < tileCountY)
	{
		listTiles[index].setTypeID(TileTypeIDSelected); //set the type of tile
	}
	else {
		std::cout << "Error: Invalid tile position." << std::endl;
	}
}
	
