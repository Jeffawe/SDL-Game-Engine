#pragma once
#include "Component.h"
#include "../Engine.h"

/// @brief A component that handles transformations.
class Transform : public Component {
public:
	Transform() = default;

	void Move(Vector2 direction) {
		Vector2 newDir = direction * speed;
		owner->position = owner->position + newDir;
	}

	void SetSpeed(int value) {
		speed = value;
	}

	//Called On Update
	void update() override {}

	//Called on render
	void render() override {}

private:
	int speed = 1;
};
