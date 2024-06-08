#include "InputManager.h"

void InputManager::Input(SDL_Event e)
{
    if (e.type == SDL_KEYDOWN) {
        if (e.key.keysym.sym == SDLK_UP) {
            currentDirection = Direction::Up;
            if (gameObjectTransform != nullptr) gameObjectTransform->Move(Vector2(0, -1));
        }

        if (e.key.keysym.sym == SDLK_DOWN) {
            currentDirection = Direction::Down;
            if (gameObjectTransform != nullptr) gameObjectTransform->Move(Vector2(0, 1));
        }

        if (e.key.keysym.sym == SDLK_LEFT) {
            currentDirection = Direction::Left;
            if (gameObjectTransform != nullptr) gameObjectTransform->Move(Vector2(-1, 0));
        }

        if (e.key.keysym.sym == SDLK_RIGHT) {
            currentDirection = Direction::Right;
            if (gameObjectTransform != nullptr) gameObjectTransform->Move(Vector2(1, 0));
        }
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
