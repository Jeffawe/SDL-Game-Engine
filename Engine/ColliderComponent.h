#pragma once
#include "Component.h"

class Collider : public Component {
	Collider();

	/**
	* @brief Checks if there was a collision with another gameObect
	*
	* @param gameObject the gameObject to check against
	* @param tag the specific tag that this is allowed to colllide with
	* @return If there was a collision with another gameObject.
	*/
	bool CheckCollision(std::shared_ptr<GameObject> gameObject, std::string tag) {
		if (gameObject->getComponent<Collider>() != nullptr) {
			bool overlapX = (owner->getPos().x + owner->getWidth() > gameObject->getPos().x) && (gameObject->getPos().x + gameObject->getWidth() > owner->getPos().x);

			// Check if the rectangles overlap along the y-axis
			bool overlapY = (owner->getPos().y + owner->getHeight() > gameObject->getPos().y) && (gameObject->getPos().y + gameObject->getHeight() > owner->getPos().y);

			return tag == "none" ? (overlapX && overlapY) : (overlapX && overlapY && tag == gameObject->tag);

		}
		else {
			return false;
		}
	}

	//Called On Update
	void update() override {
		if (owner != nullptr) {}
	}

	//Called on render
	void render() override {}
};
