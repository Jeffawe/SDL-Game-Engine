#pragma once
#include "../Engine.h"

class Transform;

class InputManager {
public:
	static InputManager& getInstance() {
		static InputManager instance;
		return instance;
	}

	void Input(SDL_Event e);

	Direction currentDirection = Direction::Down;

	Direction GetCurrentDirection() const;

	void Possess(std::shared_ptr<Character> gameObject);

private:
	// Private default constructor
	InputManager() = default;

	// Delete copy constructor and assignment operator
	InputManager(const InputManager&) = delete;
	InputManager& operator=(const InputManager&) = delete;

	std::shared_ptr<Character> possessedGameObject;
	Transform* gameObjectTransform = nullptr;
};