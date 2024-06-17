#pragma once

#include <SDL.h>
#include <string>
#include <map>
#include <type_traits>
#include <iostream>

class Character;
class GameObject;
class Camera;
class Tilemap;

struct GameObjectInfo {
	int zIndex;
	std::string name;

	bool operator==(const GameObjectInfo& other) const {
		return zIndex == other.zIndex && name == other.name;
	}
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
	virtual int Start();

	//Function runs at each update
	virtual int Update();

	void Close();

	void DebugRect(SDL_Renderer* renderer, SDL_Rect* rect, SDL_Color color);

	std::shared_ptr<GameObject> FindGameObject(int zIndex, std::string stringValue);

	const int FPS = 10; // Desired frames per second
	const int FRAME_DELAY = 1000 / FPS;

	Uint32 frameStart = 0;
	int frameTime = 0;

	Camera* camera;
	Tilemap* tilemap;

private:
	bool initSDL();

	void closeSDL();

protected:
	std::multimap<GameObjectInfo, std::shared_ptr<GameObject>, CustomComparator> gameObjects;

	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;

	std::shared_ptr<Character> player;
};

