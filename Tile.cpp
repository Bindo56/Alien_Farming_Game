#include "Tile.h"
#include "SDL2\SDL.h"
#include <vector>
#include "TextureLoader.h"



const std::vector<Tile::Type> Tile::listTileTypes = {
	{ 0, SDL_Color { 0, 67, 190, 255},   SDL_Color{0, 67, 190, 255}   }, //water
	{ 1,SDL_Color{138, 47, 50, 255},  SDL_Color{158, 56, 62, 255}  }, //Dirt
	{ 2,SDL_Color{184, 33, 117, 255}, SDL_Color{218, 50, 143, 255} }, //purple grass
	{ 2,SDL_Color{11, 100, 100, 255}, SDL_Color{14, 131, 131, 255} },//green
	{ 2,SDL_Color{184, 176, 33, 255}, SDL_Color{218, 209, 50, 255} },//yellow
	{ 2,SDL_Color{33, 41, 186, 255},  SDL_Color{50, 59, 218, 255} },//blue
	{ 2,SDL_Color{167, 167, 167, 255}, SDL_Color{199, 199, 199, 255} }
	
}; 

std::vector<SDL_Texture*> Tile::listTextureTileShadow;


Tile::Tile(SDL_Renderer* renderer) :typeID(2)
{
	//Load the shadow textures once only.
	if (listTextureTileShadow.empty()) {
		std::vector<std::string> listTileShadowNames{ "Top Left", "Top", "Top Right", "Left",
				"Right", "Bottom Left", "Bottom", "Bottom Right" };

		for (const auto& nameSelected : listTileShadowNames)
			listTextureTileShadow.push_back(TextureLoader::loadTexture(renderer,
				"Tile Shadow " + nameSelected + ".bmp"));
	}

	

}

void Tile::drawTile(SDL_Renderer* render,int x,int y, int tilesize)
{
	if (typeID > -1 && typeID < listTileTypes.size()) {
		const Type& tileType = listTileTypes[typeID];
	    bool dark = ((x + y) % 2 == 0);

		SDL_Color colorTile = dark ? tileType.corlorDark : tileType.corlorLight;

		SDL_SetRenderDrawColor(render, colorTile.r, colorTile.g, colorTile.b, 255);

		SDL_Rect rect = { x * tilesize , y * tilesize ,tilesize,tilesize };
		SDL_RenderFillRect(render, &rect);
	}

	//switch (typeID)
	//{
	//case 0: //water
	//	SDL_SetRenderDrawColor(render, 0, 67, 190, 255);
	//	break;
	//case 1://Dirt
	//	if (dark) {
	//		SDL_SetRenderDrawColor(render, 138, 47, 50, 255);
	//	}
	//	else
	//	{
	//		SDL_SetRenderDrawColor(render, 158, 56, 62, 255);
	//	}
	//	break;
	//	

	//	
	//case 2://purple grass
	//default:

	//	if (dark)
	//	{
	//		SDL_SetRenderDrawColor(render, 184, 33, 117, 255);
	//	}
	//	else
	//	{
	//		SDL_SetRenderDrawColor(render, 218, 50, 143, 255);
	//	}
	//	break;
	//}

	

}

void Tile::drawShadow(SDL_Renderer* renderer, int x, int y, int tileSize, std::vector<Tile>& listTile, int TileCountX, int TileCountY)
{
	SDL_Rect rect = { x * tileSize , y * tileSize ,tileSize , tileSize};

	for (int count = 0; count <listTextureTileShadow.size(); count++)
	{
		SDL_Texture* textureSelected = listTextureTileShadow[count];
		if (textureSelected != nullptr) {
			//map cpunt to an index on a 3x3 grid if count is in the center tile skip it 

			int index = count;
			if (count >= 4)
				index++;

			//convert index to an x any y offset rangeing from -1 to 1 fopr 3x3 grid

			int xOff = index % 3 - 1;
			int yOff = index / 3 - 1;

			//check if Offset tile is corner , then draw the shadow 
			bool isCorner = (abs(xOff) == 1 && abs(yOff) == 1);//The absolute value dont care about minus sign -3 will be 3
			if (isCorner) {
				//check if tile is higher than the other tile
				if (isTileHigher(x + xOff, y + yOff, listTile, TileCountX, TileCountY) &&
					isTileHigher(x + xOff, y, listTile, TileCountX, TileCountY) == false &&
					isTileHigher(x, y + yOff, listTile, TileCountX, TileCountY) == false) 
				{
					SDL_RenderCopy(renderer, textureSelected, NULL, &rect);
				}
			}
			else
			{
				if (isTileHigher(x + xOff, y + yOff, listTile, TileCountX, TileCountY)) {
					SDL_RenderCopy(renderer, textureSelected, NULL, &rect);
				}
			}
		}
			
	}






	/*if (isTileHigher(x, y - 1, listTile,TileCountX, TileCountY) && textureTileShadow != nullptr)
		SDL_RenderCopy(renderer, textureTileShadow, NULL, &rect);

	if (isTileHigher(x +1, y,listTile, TileCountX, TileCountY) && textureTileShadowRight != nullptr)
		SDL_RenderCopy(renderer, textureTileShadowRight, NULL, &rect);

	if (isTileHigher(x, y + 1,listTile, TileCountX, TileCountY) && textureTileShadowLeft != nullptr)
		SDL_RenderCopy(renderer, textureTileShadowLeft, NULL, &rect);

	if (isTileHigher(x - 1, y,listTile, TileCountX, TileCountY) && textureTileShadowBottom != nullptr)
		SDL_RenderCopy(renderer, textureTileShadowBottom, NULL, &rect);


	if (isTileHigher(x - 1, y - 1, listTile, TileCountX, TileCountY) && isTileHigher(x - 1, y, listTile, TileCountX, TileCountY) == false && isTileHigher(x, y - 1, listTile, TileCountX, TileCountY) == false
		&& textureTileShadowTopLeft != nullptr) {
		SDL_RenderCopy(renderer, textureTileShadowTopLeft, NULL, &rect);
	}

	if (isTileHigher(x + 1, y - 1, listTile, TileCountX, TileCountY) && isTileHigher(x + 1, y, listTile, TileCountX, TileCountY) == false && isTileHigher(x, y - 1, listTile, TileCountX, TileCountY) == false
		&& textureTileShadowTopRight != nullptr) {
		SDL_RenderCopy(renderer, textureTileShadowTopRight, NULL, &rect);
	}

	if (isTileHigher(x - 1, y + 1, listTile, TileCountX, TileCountY) && isTileHigher(x - 1, y, listTile, TileCountX, TileCountY) == false && isTileHigher(x, y + 1, listTile, TileCountX, TileCountY) == false
		&& textureTileShadowBottomLeft != nullptr) {
		SDL_RenderCopy(renderer, textureTileShadowBottomLeft, NULL, &rect);
	}

	if (isTileHigher(x + 1, y + 1, listTile, TileCountX, TileCountY) && isTileHigher(x + 1, y, listTile, TileCountX, TileCountY) == false && isTileHigher(x, y + 1, listTile, TileCountX, TileCountY) == false
		&& textureTileShadowBottomRight != nullptr) {
		SDL_RenderCopy(renderer, textureTileShadowBottomRight, NULL, &rect);
	}*/

}



void Tile::setTypeID(int id)
{
	if (id > -1 && id <= listTileTypes.size()) {

	  typeID = id;
	}
}

bool Tile::isTileHigher(int x, int y, std::vector<Tile>& listTile, int TileCountX, int tileCountY)
{
	if (typeID > -1 && typeID < listTileTypes.size()) {
		int indexOther = x + y * TileCountX;
		if (indexOther > -1 && indexOther < listTile.size() &&
			x > -1 && x < TileCountX &&
			y > -1 && y < tileCountY) {

			int typrIDOther = listTile[indexOther].typeID;

			//compare the height

			if (typrIDOther > -1 && typrIDOther < listTileTypes.size()) {
				return listTileTypes[typrIDOther].height > listTileTypes[typeID].height;
			}
		}
	}


	return false;
}
