#pragma once

#include <iostream>
#include <SDL.h>
#include <functional>

#include "../EngineValues.h"

class Character;
class Transform;

// Define an alias for the function type
using EventFunction = std::function<void()>;

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

	void registerSinglePressEvent(SDL_Keycode key, EventFunction func) {
		singlePressEvents[key] = func;
	}

	void MovePossessedObject(SDL_Keycode key);

private:
	// Private default constructor
	InputManager() = default;

	// Delete copy constructor and assignment operator
	InputManager(const InputManager&) = delete;
	InputManager& operator=(const InputManager&) = delete;

	std::shared_ptr<Character> possessedGameObject;
	Transform* gameObjectTransform = nullptr;

	std::unordered_map<SDL_Keycode, EventFunction> singlePressEvents;

	bool CanMove(int x, int y);
};