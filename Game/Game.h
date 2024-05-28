#pragma once
#include "../Engine.h"

class Game
{
public:
	Game() = default;
	SDL_Window* gWindow = NULL;
	SDL_Renderer* gRenderer = NULL;

	//Function runs once when the game starts
	int Start();

	//Function runs at each update
	int Update();

	void Close();

	void SetUpGameObjects();

	std::shared_ptr<GameObject> CreateGameObject(int _width, int _height, int _x, int _y);

private:
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;
	const int FPS = 10; // Desired frames per second
	const int FRAME_DELAY = 1000 / FPS;

	Uint32 frameStart = 0;
	int frameTime = 0;

	bool initSDL();

	void closeSDL();

	std::vector<std::shared_ptr<GameObject>> gameObjects;
};

