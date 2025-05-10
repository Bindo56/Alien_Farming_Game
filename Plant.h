#pragma once
#include "SDL2\SDL.h"
#include "TextureLoader.h"
#include "Timer.h"
#include "Vector2D.h"
#include <vector>
#include "MathAddon.h"
#include "level.h"

class Game;

class Plant
{
private:
	struct Type
	{
		std::string name = "";
		int size = 1;
		bool growsOnWetDirt = true;
	};

public:
	Plant(SDL_Renderer* renderer, int setTypeID, Vector2D setPos);
	bool checkOverlapWithMouse(int x, int y);
	bool checkOverlapWithPlantTypeID(int x, int y, int plantTypeID);
	void update(float dT);
	void Draw(SDL_Renderer* renderer, int tileSize);
	void drawShadow(SDL_Renderer* renderer, int tileSize);
	bool checkIfTilesUnderOk(level& level);
	static bool checkIfTilesUnderOkForType(int x, int y, int plantTyprID, level& level);
	static bool checkIfPositionOkForType(Vector2D posCheck, int plantTypeID, Game& game);
	bool checkCircleOverlap(Vector2D posCircle, float radiusCircle);
	Vector2D getPos();




private:
	void drawTexture(SDL_Renderer* renderer, SDL_Texture* textureSelected, int tileSize);
	bool checkOverlap(int x, int y, int size);
	static float computeOffset(int plantTypeID);
	static float computeRadius(int plantTypeID);

	Vector2D pos;
	float fDrawScale = 1.0f;
	Timer timerMoveUpAndDown, timerGrowth;

	int totalPlantType = 5;
	int typeID;
	SDL_Texture* textureMain = nullptr, * textureShadow = nullptr, * textureSmall = nullptr, * textureSmallShadow;

	static const std::vector<Type> listPlantType;
};

