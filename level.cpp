#include "level.h"
#include <iostream>
//#include "SDL2/SDL.h"

level::level(SDL_Renderer* renderer,int setTileCountX, int setTileCountY) :
	tileCountX(setTileCountX), tileCountY(setTileCountY)
{


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
			//listTiles[index].drawShadow(render, x, y, tilesize, listTiles, tileCountX, tileCountY);
			
		}
	}
}


void level::drawShadows(SDL_Renderer* renderer, int tileSize)
{
	for (int y = 0; y < tileCountY; y++)
	{
		for (int x = 0; x < tileCountX; x++)
		{
			int index = x + y * tileCountX;

			
			listTiles[index].drawShadow(renderer, x, y, tileSize, listTiles, tileCountX, tileCountY);

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

		Tile::refreshSurroundingIsWet(x, y, listTiles, tileCountX, tileCountY);
	}
	else {
		std::cout << "Error: Invalid tile position." << std::endl;
	}
}

bool level::checkIfTileOkForPlant(int x, int y, bool growsOnWetDirt)
{
	int index = x + y * tileCountX;
	if (index > -1 && index < listTiles.size() &&
		x > -1 && x < tileCountX &&
		y > -1 && y < tileCountY) {
		std::cout << "level.cpp checkIfTileOkForPlant " << listTiles[index].checkIfOkForPlant(growsOnWetDirt) << "\n";
		return listTiles[index].checkIfOkForPlant(growsOnWetDirt);
	}

	return false;
}
bool level::checkIfTileOkForAnimal(Vector2D posCheck, float radiusCircle)
{
	//check if the input are dont overlap any tile that are wrong type for animal and isnt in the bound of the level.(screensize)

	//define the rectanglke that contains the input circle.
	int rectLeft = (int)(posCheck.x - radiusCircle);
	int rectTop = (int)(posCheck.y - radiusCircle);
	int rectRight = (int)(posCheck.x + radiusCircle);
	int rectBottom = (int)(posCheck.y + radiusCircle);

	//ensure that it s within the screen bound or level
	//check the top and left falot value -0.1f cast to 0 but is out of bounds.
	if (rectLeft < 0 || rectTop < 0 || rectRight >= tileCountX || rectBottom >= tileCountY ||
		(posCheck.x - radiusCircle) < 0.0f || (posCheck.y - radiusCircle) < 0.0f) {
		return false;
	}
	else {
		//check if the circle overlap with any tile that are wrong type for animal
		for (int y = rectTop; y <= rectBottom; y++) {
			for (int x = rectLeft; x <= rectRight; x++) {
				int index = x + y * tileCountX;
				//if (index > -1 && index < listTiles.size()) {
					if (listTiles[index].CheckIfOkForAnimal(x,y,posCheck, radiusCircle) == false) {
						return false;
					}
				//}
			}
		}
	}
	return true;
}


	
