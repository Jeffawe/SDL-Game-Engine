#include "Tilemap.h"
#include "Camera.h"
#include "GameObject.h"
#include "ColliderComponent.h"
#include "Camera.h"
#include "./CollisionManager.h"

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

	for (const auto& tile : tiles) {
		Vector2 tileVector = camera.worldToScreen(Vector2(tile.x * tileSize, tile.y * tileSize), "tile");

		if (camera.canSeeVector(tileVector, tileSize, tileSize)) {
			SDL_Rect destRect = { tileVector.x, tileVector.y, tileSize, tileSize };
			SDL_Texture* text = Value2Texture(tile.value);
			if (text != nullptr) {
				SDL_RenderCopy(renderer, text, nullptr, &destRect);
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


// Function to compare tiles based on their positions
bool compareTiles(const Tile& a, const Tile& b) {
	return std::tie(a.x, a.y) < std::tie(b.x, b.y);
}

bool Tilemap::isCollidable(int x, int y, int xOffset, int yOffset, std::shared_ptr<GameObject> character) {
	if (!character) return false;

	Collider* collider = character->getComponent<Collider>();
	if (!collider) return false;

	SDL_Rect colliderRect = { collider->GetBoundingBox()->x + xOffset, collider->GetBoundingBox()->y + yOffset, collider->GetBoundingBox()->w, collider->GetBoundingBox()->h };

	// Create a dummy tile to use for binary search
	Vector2 targetTile;
	targetTile.x = x / tileSize;
	targetTile.y = y / tileSize;

	Tile* tile = findTile(targetTile.x + xOffset, targetTile.y + yOffset);

	// Make the Collision Rect finding more specific 

	if (tile != nullptr) {
		Camera& camera = Camera::getInstance();
		CollisionManager& collisionManager = CollisionManager::getInstance();
		auto value = collisionMap.find(tile->value);
		if (value != collisionMap.end() && value->second == true) {
			Vector2 tileVector = camera.worldToScreen(Vector2(tile->x * tileSize, tile->y * tileSize), "tile");
			std::cout << "Target Tile with value 1 at (" << tileVector.x << ", " << targetTile.y << ")" << std::endl;
			collisionRect = { tileVector.x, tileVector.y, tileSize, tileSize };

			return SDL_HasIntersection(&colliderRect, &collisionRect);
		}
	}

	// Only check for intersection if collisionRect is not a zero rectangle
	if (collisionRect.w > 0 && collisionRect.h > 0) {
		return SDL_HasIntersection(&colliderRect, &collisionRect);
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
	auto it = tilemaps.find(value);
	return it != tilemaps.end() ? it->second : nullptr;
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

		if (currentX + tilebaseWidth > maxTilesX) {
			currentX = 0;
			currentY += tilebaseHeight;
		}

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

				combinedMap.push_back({ currentX + x, currentY + y, tilebase.tiles[y][x] });
			}
		}

		currentX += tilebaseWidth;
	}

	return combinedMap;
}

Tile* Tilemap::findTile(int x, int y)
{
	auto it = std::find_if(tiles.begin(), tiles.end(), [x, y](const Tile& tile) {
		return tile.x == x && tile.y == y;
	});

	return it != tiles.end() ? &(*it) : nullptr;
}
