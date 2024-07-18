#pragma once

#include "Component.h"
#include <SDL.h>
#include "../EngineValues.h"

/**
* @brief Registers Collisions with other GameObjects and Tilemap Colliders
*/
class Collider : public Component {
public:
	Collider() : boundingBox(new SDL_Rect()), width(0), height(0) {}


	/**
	* @brief Checks if there was a collision with another gameObject
	*
	* @param gameObject: the gameObject to check against
	* @param tag: the specific tag that this is allowed to collide with
	* @return If there was a collision with another gameObject.
	*/
	bool CheckCollision(std::shared_ptr<GameObject> gameObject, std::string tag) const {
		if (gameObject->getComponent<Collider>() != nullptr) {
			SDL_Rect* colliderRect = gameObject->getComponent<Collider>()->boundingBox;
			return tag == "none" ? SDL_HasIntersection(boundingBox, colliderRect) : (SDL_HasIntersection(boundingBox, colliderRect) && tag == gameObject->tag);
		}

		return false;
	}

	/**
	* @brief Returns the Collision Box
	*/
	SDL_Rect* GetBoundingBox() {
		return boundingBox;
	}

	void start() override {
		updateBoundingBox();
	}

	/**
	* @brief Changes the Size of the Collision Box
	*
	* @param _width: The width to set the collision box
	* @param _height: The height to set the collision box
	* @param colliderPos (Optional): The Position to set the collider at
	*/
	void SetColliderSize(int _width, int _height, Vector2 colliderPos = Vector2::zero) {
		if (width == boundingBox->w && height == boundingBox->h) return;
		width = _width;
		height = _height;
		useCustomPos = true;

		if (colliderPos != Vector2::zero) {
			colliderXY.x = colliderPos.x;
			colliderXY.y = colliderPos.y;
		}
		else {
			colliderXY.x = (owner->getWidth() - width) / 2;
			colliderXY.y = (owner->getHeight() - height) / 2;
		}

		updateBoundingBox();
	}

	void update() override {
		updateBoundingBox();
	}

	//Called on render
	void render() override {}

	void close() override {}

private:
	SDL_Rect* boundingBox;

	int height;
	int width;
	bool useCustomPos;

	Vector2 colliderXY;

	void updateBoundingBox() {
		if (owner != nullptr) {
			boundingBox->x = owner->getPos().x + colliderXY.x;
			boundingBox->y = owner->getPos().y + colliderXY.y;
			boundingBox->w = (useCustomPos) ? width : owner->getWidth();
			boundingBox->h = (useCustomPos) ? height : owner->getHeight();
		}
	}
};
