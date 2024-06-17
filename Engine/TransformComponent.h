#pragma once

#include "Component.h"

/**
* @brief A component that handles transformations
*/
class Transform : public Component {
public:
	Transform() = default;

	void Move(Vector2 direction) {
		if (!canMove) return;
		Vector2 newDir = direction * speed;
		owner->position = owner->position + newDir;
		owner->ChangeDestRect();
	}

	void SetSpeed(int value) {
		speed = value;
	}

	void SetCanMove(bool _canMove) {
		canMove = _canMove;
	}

	bool GetCanMove() const {
		return canMove;
	}
	void start() override {}

	//Called On Update
	void update() override {}

	//Called on render
	void render() override {}

	void close() override {}

private:
	int speed = 1;
	bool canMove = true;
};
