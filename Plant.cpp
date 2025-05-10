#include "Plant.h"
#include "Game.h"
#include <iostream>


const std::vector <Plant::Type> Plant::listPlantType = {

	{"Plant 1" , 1, true},
	{"Plant 2" , 1, true},
	{"Plant 3" , 1,false},
	{"Plant 4" , 2,false},
	{"Plant 5" , 2,false}

};


Plant::Plant(SDL_Renderer* renderer, int setTypeID, Vector2D setPos) :typeID(setTypeID), pos(setPos), timerGrowth(6.5f + MathAddon::randFloat() * 6.5f), timerMoveUpAndDown(2.0f, MathAddon::randFloat() * 2.0f)
{
	std::cout << setTypeID;

	if (setTypeID > -1 && setTypeID < listPlantType.size()) {

		std::string name = listPlantType[setTypeID ].name;
		textureSmall = TextureLoader::loadTexture(renderer, name + " Small.bmp");
		textureSmallShadow = TextureLoader::loadTexture(renderer, name + " Small Shadow.bmp");
	//	SDL_SetTextureAlphaMod(textureSmallShadow, (int)round(255 * 0.60f));

		textureMain = TextureLoader::loadTexture(renderer, name + ".bmp");
		textureShadow = TextureLoader::loadTexture(renderer, name + " Shadow.bmp");
		//SDL_SetTextureAlphaMod(textureShadow, (int)round(255 * 0.60f));

		//Offset the plant's posi

		pos += computeOffset(setTypeID);

	}
}


void Plant::update(float dT)
{
	timerGrowth.countUp(dT);

	timerMoveUpAndDown.countUp(dT);
	if (timerMoveUpAndDown.timeSIsMax())
		timerMoveUpAndDown.resetToZero();

	float fDrawScaleMin = 0.95f;
	float fCos = (cos(timerMoveUpAndDown.computeFTime() * 2.0f * MathAddon::PI) + 1.0f) / 2.0f;
	fDrawScale = fDrawScaleMin + (1.0f - fDrawScale) * fCos;
}

void Plant::Draw(SDL_Renderer* renderer, int tileSize) {

	if (timerGrowth.timeSIsMax()) {
		
		drawTexture(renderer, textureMain, tileSize);
	}
	else {
		
		drawTexture(renderer, textureSmall, tileSize);
	}

}

void Plant::drawShadow(SDL_Renderer* renderer, int tileSize)
{
	if (timerGrowth.timeSIsMax()) {
		drawTexture(renderer, textureShadow, tileSize);

	}
	else {
		drawTexture(renderer, textureSmallShadow, tileSize);
	}
}


void Plant::drawTexture(SDL_Renderer* renderer, SDL_Texture* textureSelected, int tileSize)
{
	if (renderer != nullptr && textureSelected != nullptr) {
		int w, h;
		SDL_QueryTexture(textureSelected, NULL, NULL, &w, &h);

		w = (int)round(w * fDrawScale);
		h = (int)round(h * fDrawScale);

		SDL_Rect rect = {
			(int)round(pos.x * tileSize) - w / 2,
			(int)round(pos.y * tileSize) - h / 2,
			w,
			h };

		SDL_RenderCopy(renderer, textureSelected, NULL, &rect);
	}


}

bool Plant::checkOverlapWithPlantTypeID(int x, int y, int plantTypeID)
{
	if (plantTypeID > -1 && plantTypeID < listPlantType.size())
	{
		return checkOverlap(x, y, listPlantType[plantTypeID].size);
	}

	return false;
}

bool Plant::checkOverlapWithMouse(int x, int y)
{

	return checkOverlap(x, y, 1);
}


bool Plant::checkOverlap(int x, int y, int size)
{ //setup the rectangle that represent the tile that hel;ps to see the ovelap and another rectangle the input , thenm checl if they overlap
	if (typeID > -1 && typeID < listPlantType.size()) {

		float offset1 = computeOffset(typeID);

		int rect1Left = (int)(pos.x - offset1);
		int rect1Top = (int)(pos.y - offset1);
		int rect1Right = rect1Left + listPlantType[typeID].size - 1;
		int rect1Bottom = rect1Top + listPlantType[typeID].size - 1;

		int rect2Left = x;
		int rect2Top = y;
		int rect2Right = rect2Left + size - 1;
		int rect2Bottom = rect2Top + size - 1;

		return ((rect1Left > rect2Right || rect2Left > rect1Right || rect1Top > rect2Bottom || rect2Top > rect1Bottom) == false);

	}

	return false;
}

float Plant::computeOffset(int plantTypeID)
{
	if (plantTypeID > -1 && plantTypeID < listPlantType.size()) {
		return (listPlantType[plantTypeID].size - 1) / 2.0f;
	}
	return 0.0f;
}

float Plant::computeRadius(int plantTypeID)
{
	if (plantTypeID > -1 && plantTypeID < listPlantType.size()) {
		return (listPlantType[plantTypeID].size * 0.80f / 2.0f);
	}
	return 0.0f;
}

bool Plant::checkIfTilesUnderOk(level& level)
{
	float offset = computeOffset(typeID);

	int x = (int)(pos.x - offset);
	int y = (int)(pos.y - offset);

	return checkIfTilesUnderOkForType(x, y, typeID, level);
}


bool Plant::checkIfTilesUnderOkForType(int x, int y, int plantTyprID, level& level)
{
	if (plantTyprID > -1 && plantTyprID < listPlantType.size()) {
		const Type& typeSelected = listPlantType[plantTyprID];

		int rectLeft = x;
		int rectTop = y;
		int rectRight = rectLeft + typeSelected.size - 1;
		int rectBottom = rectTop + typeSelected.size - 1;

		for (int y2 = rectTop; y2 <= rectBottom; y2++) {
			for (int x2 = rectLeft; x2 <= rectRight; x2++)
			{
				if (level.checkIfTileOkForPlant(x2, y2, typeSelected.growsOnWetDirt) == false) {
					//std::cout << "false from here checkIfTilesUnderOkForTypeFalse" << "\n";
				    return false;
				}
			}
		}
		//std::cout << "CheckIfTilesUnderOkForType true return";
     	return true;
	}
	//std::cout << "false from here checkIfTilesUnderOkForTypeFalse";
	return false;
}

bool Plant::checkIfPositionOkForType(Vector2D posCheck, int plantTypeID, Game& game)
{
	if (plantTypeID > -1 && plantTypeID < listPlantType.size()) {

		level level = game.getLevel();
		if (checkIfTilesUnderOkForType((int)posCheck.x, (int)posCheck.y, plantTypeID
			, level) == false) {
			return false;
		}
		Vector2D posCheckWithOffset = posCheck + computeOffset(plantTypeID);
		float radiusCheck = computeRadius(plantTypeID);

		for (auto& animalSelected : game.getListAnimals())
		{
			if (animalSelected.checkCircleOverlap(posCheckWithOffset, radiusCheck)) {
				return false;
			}
		}

		for (auto& plantSelected : game.getListPlants()) {
			if (plantSelected.checkOverlapWithPlantTypeID((int)posCheck.x, (int)posCheck.y, plantTypeID)) {
				return false;
			}
		}

		return true;
	}

	return false;
}

bool Plant::checkCircleOverlap(Vector2D posCircle, float radiusCircle)
{
	if (typeID > -1 && typeID < listPlantType.size()) {
		float radius = listPlantType[typeID].size * 0.80f / 2.0f;
		return (pos - posCircle).magnitude() <=  (computeRadius(typeID) + radiusCircle);
	}
	return false;
}




Vector2D Plant::getPos()
{
	return pos;
}


