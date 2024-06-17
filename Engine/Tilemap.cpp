#include "Tilemap.h"
#include "Camera.h"
#include "GameObject.h"
#include "ColliderComponent.h"

void Tilemap::CreateNewTile(int tileKey, SDL_Texture* tileText, bool isCollidable)
{
	tilemaps[tileKey] = tileText;
	collisionMap[tileKey] = isCollidable;
}

void Tilemap::GenerateTileMap(const std::vector<TileBase>& tilemaps, int screenWidth, int screenHeight, int _tileSize, SDL_Renderer* _renderer)
{
	tileSize = _tileSize;
	renderer = _renderer;
	tiles = combineTilemaps(tilemaps, screenWidth, screenHeight);
}

void Tilemap::Update()
{
	if (tiles.empty()) return;

	Camera& camera = Camera::getInstance();

	for (auto& tile : tiles) {
		Vector2 tileVector = camera.worldToScreen(Vector2(tile.x * tileSize, tile.y * tileSize), "tile");

		if (camera.canSeeVector(tileVector, tileSize, tileSize)) {
			SDL_Rect destRect = { tileVector.x, tileVector.y, tileSize, tileSize };
			SDL_Texture* text = Value2Texture(tile.value);
			if (text != nullptr) {
				SDL_RenderCopy(renderer, text, NULL, &destRect);
			}
		}
	}
}

void Tilemap::Close()
{
	tiles.clear();

	for (auto& tile : tilemaps) {
		SDL_DestroyTexture(tile.second);
	}

	tilemaps.clear();
	collisionMap.clear();
}

bool Tilemap::isCollidable(int x, int y, std::shared_ptr<GameObject> character)
{
	int tileX = x / tileSize;
	int tileY = y / tileSize;
	Tile* tile = findTile(tileX, tileY);

	if (tile != nullptr && character->getComponent<Collider>()) {
		Collider* collider = character->getComponent<Collider>();
		collisionRect = { tile->x * tileSize, tile->y * tileSize, tileSize, tileSize };

		if (SDL_HasIntersection(collider->GetBoundingBox(), &collisionRect)) {
			// Check if the tile value is in the collisionMap
			auto value = collisionMap.find(tile->value);
			if (value != collisionMap.end()) {
				return value->second;
			}
		}
	}
	// Return false if the tile is not found or the tile value is not in the collisionMap
	return false;
}

void Tilemap::DebugCollisions(SDL_Renderer* renderer, SDL_Color color) const
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

	// Draw the rectangle outline
	SDL_RenderDrawRect(renderer, &collisionRect);

	// Render the changes to the screen
	SDL_RenderPresent(renderer);
}

SDL_Texture* Tilemap::Value2Texture(int value)
{
	if (tilemaps.find(value) != tilemaps.end()) {
		return tilemaps[value];
	}
	else {
		return nullptr;
	}
}

std::vector<Tile> Tilemap::combineTilemaps(const std::vector<TileBase>& tilemaps, int screenWidth, int screenHeight) const
{
	std::vector<Tile> combinedMap;
	int maxTilesX = screenWidth / tileSize;
	int maxTilesY = screenHeight / tileSize;

	int currentX = 0;
	int currentY = 0;
	for (const auto& tilebase : tilemaps) {
		int tilebaseWidth = tilebase.tiles[0].size();
		int tilebaseHeight = tilebase.tiles.size();

		// Check if the tilemap fits in the current row
		if (currentX + tilebaseWidth > maxTilesX) {
			currentX = 0;
			currentY += tilebaseHeight;
		}

		// Check if the tilemap fits in the screen vertically
		if (currentY >= maxTilesY) {
			std::cerr << "Tilemaps exceed screen height!" << std::endl;
			break;
		}

		for (int y = 0; y < tilebaseHeight; ++y) {
			if (currentY + y >= maxTilesY) {
				std::cerr << "Tilemap exceeds screen height at row " << y << std::endl;
				break;
			}

			for (int x = 0; x < tilebaseWidth; ++x) {
				if (currentX + x >= maxTilesX) {
					std::cerr << "Tilemap exceeds screen width at column " << x << std::endl;
					break;
				}

				Tile tile{};
				tile.x = currentX + x;
				tile.y = currentY + y;
				tile.value = tilebase.tiles[y][x];
				combinedMap.push_back(tile);
			}
		}
	}

	return combinedMap;
}

Tile* Tilemap::findTile(int x, int y)
{
	auto it = std::find_if(tiles.begin(), tiles.end(), [x, y](const Tile& tile) {
		return tile.x == x && tile.y == y;
	});

	if (it != tiles.end()) {
		return &(*it);
	}
	else {
		return nullptr;
	}
}
