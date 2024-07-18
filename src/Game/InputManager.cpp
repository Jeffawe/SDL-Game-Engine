#include "InputManager.h"
#include "../Engine/Character.h"
#include "../Engine/TransformComponent.h"
#include "../Engine/Tilemap.h"

void InputManager::Input(SDL_Event e)
{
	if (e.type == SDL_KEYDOWN) {
		SDL_Keycode key = e.key.keysym.sym;

		if (singlePressEvents.find(key) != singlePressEvents.end()) {
			singlePressEvents[key]();
		}

		MovePossessedObject(key);
	}
}

Direction InputManager::GetCurrentDirection() const
{
	return currentDirection;
}

void InputManager::Possess(std::shared_ptr<Character> gameObject)
{
	possessedGameObject = gameObject;
	if (possessedGameObject != nullptr && possessedGameObject->getComponent<Transform>() != nullptr) {
		gameObjectTransform = possessedGameObject->getComponent<Transform>();
	}
}

void InputManager::MovePossessedObject(SDL_Keycode key)
{
	if (key == SDLK_UP || key == SDLK_w) {
		currentDirection = Direction::Up;

		if (gameObjectTransform != nullptr && CanMove(0, -1)) gameObjectTransform->Move(Vector2(0, -1));
	}

	if (key == SDLK_DOWN || key == SDLK_s) {
		currentDirection = Direction::Down;
		if (gameObjectTransform != nullptr && CanMove(0, 1)) gameObjectTransform->Move(Vector2(0, 1));
	}

	if (key == SDLK_LEFT || key == SDLK_a) {
		currentDirection = Direction::Left;
		if (gameObjectTransform != nullptr && CanMove(-1, 0)) gameObjectTransform->Move(Vector2(-1, 0));
	}

	if (key == SDLK_RIGHT || key == SDLK_d) {
		currentDirection = Direction::Right;
		if (gameObjectTransform != nullptr && CanMove(1, 0)) gameObjectTransform->Move(Vector2(1, 0));
	}
}

bool InputManager::CanMove(int xOffset, int yOffset)
{
	Tilemap& tilemap = Tilemap::getInstance();
	int newX = possessedGameObject->getPos().x + xOffset;
	int newY = possessedGameObject->getPos().y + yOffset;

	switch (currentDirection)
	{
	case Direction::Left:
		newX = possessedGameObject->getPos().x + xOffset;
		break;
	case Direction::Right:
		newX = possessedGameObject->getPos().x + possessedGameObject->getWidth() + xOffset;
		break;
	case Direction::Up:
		newY = possessedGameObject->getPos().y + yOffset;
		break;
	case Direction::Down:
		newY = possessedGameObject->getPos().y + possessedGameObject->getHeight() + yOffset;
		break;
	default:
		break;
	}

	return !tilemap.isCollidable(newX, newY, possessedGameObject);
}
