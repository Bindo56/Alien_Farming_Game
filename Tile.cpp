#include "Tile.h"
#include "SDL2\SDL.h"
#include <vector>
#include "TextureLoader.h"



const std::vector<Tile::Type> Tile::listTileTypes = {
	{"water", 0, SDL_Color {0, 67, 190, 255},   SDL_Color{0, 67, 190, 255}}, //water
	{"dirt",1,SDL_Color{138, 47, 50, 255},  SDL_Color{158, 56, 62, 255}}, //Dirt
	{"grassPurple",2,SDL_Color{184, 33, 117, 255}, SDL_Color{218, 50, 143, 255}}, //purple grass
	{"grassGreen",2,SDL_Color{11, 100, 100, 255}, SDL_Color{14, 131, 131, 255}},//green
	{"grassYellow",2,SDL_Color{184, 176, 33, 255}, SDL_Color{218, 209, 50, 255}},//yellow
	{"grassBlue",2,SDL_Color{33, 41, 186, 255},  SDL_Color{50, 59, 218, 255}},//blue
	{"grassWhite",2,SDL_Color{167, 167, 167, 255}, SDL_Color{199, 199, 199, 255}}
	
}; 

std::vector<SDL_Texture*> Tile::listTextureTileShadow;
//const std::vector<Type> Tile::listTileTypes;

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
		//if its wet dirt then make it darker
		if (tileType.name == "dirt" && isWet) {
			const float fWet = 0.65f;
			colorTile.r = (Uint8)(colorTile.r * fWet);
			colorTile.g = (Uint8)(colorTile.g * fWet);
			colorTile.b = (Uint8)(colorTile.b * fWet);
		}
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

void Tile :: refreshSurroundingIsWet(int x, int  y, std::vector<Tile>& listTile, int TileCountX, int tileCountY) {

	using distance = int;
	distance distanceTile = 2; //how far the water can spread
	//loop through any tile surrounding the input x,y pos
	for (int x2 = x - distanceTile; x2 <= x + distanceTile; x2++) {
		for (int y2 = y - distanceTile; y2 <= y + distanceTile; y2++)
		{
			int index = x2 + y2 * TileCountX;
			if (index > -1 && index < listTile.size() && x2 > -1 && x2 < TileCountX && y2 > -1 && y2 < tileCountY)
			{
				bool foundWater = false;//check if any tile surrounding is water 
				for (int x3 = x2 - distanceTile; x3 <= x2 + distanceTile; x3++) {
					for (int y3 = y2 - distanceTile; y3 <= y2 + distanceTile; y3++)
					{
						int index2 = x3 + y3 * TileCountX;
						if (index2 > -1 && index2 < listTile.size() && x3 > -1 && x3 < TileCountX && y3 > -1 && y3 < tileCountY)
						{

							int typeIDSelected = listTile[index2].typeID;
							if (typeIDSelected > -1 && typeIDSelected < listTileTypes.size() && listTileTypes[typeIDSelected].name == "water") {
								foundWater = true;
							}
						}
					}
				}
				//set isWet for selecteddTile
				listTile[index].isWet = foundWater;
			}
		}
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

bool Tile::checkIfOkForPlant(bool growsOnWetDirt)
{
	/*if (typeID > -1 && typeID < listTileTypes.size()) {
		if (listTileTypes[typeID].name == "water") {
			return false;
		}
	}
	else if (listTileTypes[typeID].name == "dirt") {
		std::cout << (growsOnWetDirt ? isWet : false) << "Tile.cpp checkifokPlant " << "\n";
		return (growsOnWetDirt ?  false : true);
	}
	else if (listTileTypes[typeID].name.substr(0, 5) == "grass") {
		return(growsOnWetDirt ? false : true);
	}
	std::cout << "Tile.cpp checkifokPlant Not Running" << "\n";
	return false;*/

	if (typeID < 0 || typeID >= listTileTypes.size()) {
		std::cout << "Tile.cpp checkifokPlant Invalid typeID\n";
		return false; // Early exit if invalid
	}

	const std::string& tileName = listTileTypes[typeID].name;

	if (tileName == "water") {
		return false;
	}
	else if (tileName == "dirt") {
		std::cout << (growsOnWetDirt ? isWet : false) << " Tile.cpp checkifokPlant (dirt)\n";
		return (growsOnWetDirt ? isWet : true);
	}
	else if (tileName.substr(0, 5) == "grass") {
		return (growsOnWetDirt ? false : true);
	}

	std::cout << "Tile.cpp checkifokPlant Not Matching Any Type\n";
	return false;
}

bool Tile::CheckIfOkForAnimal(int x , int y ,Vector2D posCheck, float radiusCircle)
{
	if (typeID > -1 && typeID < listTextureTileShadow.size()) {
		//check if the input circle overlaps this tile or not.
		//std::cout << "tile check before overlap " << x <<":x" << y << ":y" << posCheck.x << ":" << posCheck.y << radiusCircle << ":rc" << '\n';
		if (CheckCircleOverlap(x, y, posCheck, radiusCircle)) {

		//	std::cout << "tile check >"<< '\n';
			const std::string& tileName = listTileTypes[typeID].name;

			if (tileName == "water") {
			//	std::cout << tileName << ":tilename" << '\n';
				return false;
			}
			else if (tileName == "dirt") {
				//std::cout << tileName << ":tilename" << '\n';
				//std::cout << (growsOnWetDirt ? isWet : false) << " Tile.cpp checkifokPlant (dirt)\n";
				return true;
			}
			else if (tileName.substr(0, 5) == "grass") {
			//	std::cout << tileName << ":tilename" << '\n';
				return true;
			}

			//if (listTileTypes[typeID].name == "water") {
			//	return false;
			//}
			//else if (listTileTypes[typeID].name == "dirt") {
			//	return true;
			//}
			//else if (listTileTypes[typeID].name == "grass") {//.substr(0, 5) 
			//	return true;
			//}

		}
		return true;
	}
	return false;
}

bool Tile::CheckCircleOverlap(int x, int y, Vector2D posCircle, float radiusCheck) {
	//defione a rectangle for the edges of the tile

	float rectLeft = (float)(x);
	float rectTop = (float)(y);
	float rectRight = (float)(x + 1);
	float rectBottom = (float)(y + 1);

	//start with the center of the circle 
	Vector2D posCheck(posCircle);

	//comstrain posCheck to be within the tile or on the edges
	posCheck.x = std::min(std::max(posCheck.x, rectLeft), rectRight);
	posCheck.y = std::min(std::max(posCheck.y, rectTop), rectBottom);

//	std::cout << "tile overlap check" << posCheck.x << ":" << posCheck.y<< '\n';

	std :: cout << (float)((posCircle - posCheck).magnitude() < radiusCheck) << '\n';
	//Then check if the posCheck is within the circle or not.
	return ((posCircle - posCheck).magnitude() < radiusCheck);
	

}
