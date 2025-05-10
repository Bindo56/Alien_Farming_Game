#pragma once
#include <chrono>
#include "SDL2/SDL.h"
#include "TextureLoader.h"
#include "Vector2D.h"
#include "level.h"
#include <vector>
#include "Plant.h"
#include "Animal.h"




class Game
{
private : 
	enum class PlacementMode {
		tile,
		plants,
		animals

	}placementModeCurrent;


public:
	Game(SDL_Window* window, SDL_Renderer* renderer, int windowWidth, int windowHeight);
	~Game();
	level getLevel() { return level; }
	std::vector<Plant> getListPlants() { return listPlants; } 
	std::vector<Animal> getListAnimals() { return listAnimals; }
	void Run(SDL_Renderer* sdl);


private:
	void processEvents(SDL_Renderer* renderer,bool& running);
	void update(float dT);
	void draw(SDL_Renderer* renderer);
	void addPlants(SDL_Renderer* renderer,Vector2D posMouse);
	void addAnimal(SDL_Renderer* renderer,Vector2D posMouse);
	void removePlantsAtMousePosition(Vector2D posMouse);
	void setPlantTypeIDSelected(int setTypeIDSelected);
	void removePlantsIfTilesChanges();
	void removeAnimalsIfTilesChanges();
	void removeAnimalAtMousePos(Vector2D posMouse);
	void setAnimalTypeIDSelected(int setAnimalTypeID);
	int mouseDownStatus = 0;
	const int tileSize = 64;
	level level;  //initilize this construtor//Since level is a member object of class Game, it must be constructed when the Game object is constructed.//excution order 

	int animalTypeIDSelected = 0;
	int plantTypeIDSelected = 0;
	std::vector<Plant> listPlants;
	std::vector<Animal> listAnimals;

	SDL_Texture* textureShadows = nullptr;


};