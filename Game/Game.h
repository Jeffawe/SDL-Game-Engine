#pragma once
#include "../Engine.h"

struct GameObjectInfo {
	int zIndex;
	std::string name;
};

struct CustomComparator {
	bool operator()(const GameObjectInfo& a, const GameObjectInfo& b) const {
		return a.zIndex < b.zIndex;
	}
};

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

	std::shared_ptr<GameObject> FindGameObject(std::string stringValue);

	std::shared_ptr<GameObject> CreateGameObject(int _width, int _height, Vector2 pos, std::string tag, int zIndex);

private:
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;
	const int FPS = 10; // Desired frames per second
	const int FRAME_DELAY = 1000 / FPS;

	Uint32 frameStart = 0;
	int frameTime = 0;

	bool initSDL();

	void closeSDL();

	void SetUpGameObjects();

	std::multimap<GameObjectInfo, std::shared_ptr<GameObject>, CustomComparator> gameObjects;
};

