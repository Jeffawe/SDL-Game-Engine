#pragma once

#include <SDL.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include "../EngineValues.h"

class GameObject;

struct Tile {
	int x;
	int y;

	int value;
};

struct TileBase {
	std::vector<std::vector<int>> tiles;

	TileBase(const std::vector<std::vector<int>>& data) : tiles(data) {}
};

class Tilemap {
public:
	// Singleton instance access
	static Tilemap& getInstance() {
		static Tilemap instance;
		return instance;
	}

	void CreateNewTile(int tileKey, SDL_Texture* tileText, bool isCollidable);

	void GenerateTileMap(const std::vector<TileBase>& tilemaps, int screenWidth, int screenHeight, int tileSize, SDL_Renderer* _renderer);

	void Update();

	void Close();

	bool isCollidable(int x, int y, std::shared_ptr<GameObject> character);

	void DebugCollisions(SDL_Renderer* renderer, SDL_Color color) const;

private:
	Tilemap() { renderer = nullptr; tileSize = 30; collisionRect = { 0,0,0,0 }; };
	~Tilemap() { Close(); }

	SDL_Texture* Value2Texture(int value);

	std::vector<Tile> combineTilemaps(const std::vector<TileBase>& tilemaps, int screenWidth, int screenHeight) const;

	int tileSize;

	SDL_Rect collisionRect;

	SDL_Renderer* renderer;

	Tile* findTile(int x, int y);

	std::vector<Tile> tiles;

	std::unordered_map<int, SDL_Texture*> tilemaps;

	std::unordered_map<int, bool> collisionMap;

	// Prevent copying and assignment
	Tilemap(const Tilemap&) = delete;
	Tilemap& operator=(const Tilemap&) = delete;
};