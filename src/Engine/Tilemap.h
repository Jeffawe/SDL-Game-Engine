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

	/**
	* Creates a new tile and adds it to the tilemap.
	*
	* @param tileKey The key for the tile in the tilemap.
	* @param tileText The SDL_Texture for the tile.
	* @param isCollidable A boolean indicating if the tile is collidable.
	*/
	void CreateNewTile(int tileKey, SDL_Texture* tileText, bool isCollidable);

	/**
	* Generates the tilemap based on the provided tiles and screen dimensions.
	*
	* @param tilemaps A vector of TileBase containing the tilemap information.
	* @param screenWidth The width of the screen.
	* @param screenHeight The height of the screen.
	* @param _tileSize The size of each tile.
	* @param _renderer The SDL_Renderer used to render the tiles.
	*/
	void GenerateTileMap(const std::vector<TileBase>& tilemaps, int screenWidth, int screenHeight, int tileSize, SDL_Renderer* _renderer);

	void Update();

	void Close();

	/**
	* @brief Determines if there is a collidable tile in front of a character based on its position.
	*
	* This function checks if there is a tile in front of the character at the specified coordinates
	* that is considered collidable. It does this by calculating the tile position from the given
	* coordinates, checking for collisions using the character's collider, and then verifying if
	* the tile's value is present in the collision map.
	*
	* @param x - The x-coordinate of the position to check.
	* @param y - The y-coordinate of the position to check.
	* @param character - A shared pointer to the character (or player) involved in the collision check.
	* @return True if there is a collidable tile in front of the character, otherwise false.
	*/
	bool isCollidable(int x, int y, int xOffset, int yOffset, std::shared_ptr<GameObject> character);

	/**
	* Renders a debug visualization of the collision rectangles.
	*
	* @param renderer The SDL_Renderer used to draw the collision rectangles.
	* @param color The color used to draw the collision rectangles.
	*/
	void DebugCollisions(SDL_Renderer* renderer, SDL_Color color) const;

private:
	Tilemap() { renderer = nullptr; tileSize = 30; collisionRect = { 0,0,0,0 }; sensitivity = 0;  };
	~Tilemap() { Close(); }

	/**
	* Combines multiple tilemaps into a single vector of tiles based on screen dimensions.
	*
	* @param tilemaps A vector of TileBase containing the tilemap information.
	* @param screenWidth The width of the screen.
	* @param screenHeight The height of the screen.
	* @return A combined vector of Tile objects.
	*/
	SDL_Texture* Value2Texture(int value);

	/**
	* Combines multiple tilemaps into a single vector of tiles based on screen dimensions.
	*
	* @param tilemaps A vector of TileBase containing the tilemap information.
	* @param screenWidth The width of the screen.
	* @param screenHeight The height of the screen.
	* @return A combined vector of Tile objects.
	*/
	std::vector<Tile> combineTilemaps(const std::vector<TileBase>& tilemaps, int screenWidth, int screenHeight) const;

	int tileSize;

	int sensitivity;

	SDL_Rect collisionRect;

	SDL_Renderer* renderer;

	/**
	* Finds a tile at the specified coordinates.
	*
	* @param x The x-coordinate of the tile.
	* @param y The y-coordinate of the tile.
	* @return A pointer to the Tile object if found, otherwise nullptr.
	*/
	Tile* findTile(int x, int y);

	std::vector<Tile> tiles;

	std::unordered_map<int, SDL_Texture*> tilemaps;

	std::unordered_map<int, bool> collisionMap;

	// Prevent copying and assignment
	Tilemap(const Tilemap&) = delete;
	Tilemap& operator=(const Tilemap&) = delete;
};