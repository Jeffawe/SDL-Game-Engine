#pragma once

#include "../EngineValues.h"
#include <SDL.h>
#include "./Character.h"
#include "./GameObject.h"

class Camera
{
public:
	// Singleton instance access
	static Camera& getInstance() {
		static Camera instance;
		return instance;
	}

	// Convert world coordinates to screen coordinates
	Vector2 worldToScreen(const Vector2& worldPos, const std::string& tag) const {
		if (possessedCharacter && tag != "RUN") {
			return worldPos - Vector2(cameraRect.x, cameraRect.y);
		}

		return worldPos;
	}

	/**
	* @brief Sets the camera rectangle and screen dimensions.
	*
	* @param width The width of the camera rectangle.
	* @param height The height of the camera rectangle.
	* @param screen_width The width of the screen.
	* @param screen_height The height of the screen.
	*/
	void setRect(int width, int height, int screen_width, int screen_height) {
		cameraRect = { 0, 0, width, height };
		Screen_Width = screen_width;
		Screen_Height = screen_height;
	}

	/**
	* @brief Possesses a character for the engine to control.
	*
	* @param _possessedCharacter A shared pointer to the GameObject to possess.
	*/
	void Possess(std::shared_ptr<GameObject> _possessedCharacter) {
		possessedCharacter = _possessedCharacter;
	}

	void updateRect() {
		if (possessedCharacter != nullptr) {
			cameraRect.x = possessedCharacter->getPos().x - cameraRect.w / 2;
			cameraRect.y = possessedCharacter->getPos().y - cameraRect.h / 2;

			if (cameraRect.x < 0) cameraRect.x = 0;
			if (cameraRect.y < 0) cameraRect.y = 0;
			if (cameraRect.x >= cameraRect.w) cameraRect.x = cameraRect.w;
			if (cameraRect.y >= cameraRect.h) cameraRect.y = cameraRect.h;
		}
	}

	/**
	* @brief Checks if a given position is within the visible area of the camera.
	*
	* This function determines if a specified rectangular area (defined by its position, width, and height)
	* is within the bounds of the camera's visible rectangle. The check accounts for an offset to ensure
	* that objects partially within the view are also considered visible.
	*
	* @param position The position of the object as a `Vector2` structure.
	* @param width The width of the object.
	* @param height The height of the object.
	* @return True if the object is within the visible area of the camera; otherwise, false.
	*/
	bool canSeeVector(Vector2 position, int width, int height) const {
		if (position.x + width + offset >= 0 && position.x - offset < cameraRect.w &&
			position.y + height + offset >= 0 && position.y - offset < cameraRect.h)
		{
			return true;
		}
		else {
			return false;
		}
	}

	/**
	* @brief Checks if a character is out of the screen bounds.
	*
	* This function determines if the given character is out of the specified screen bounds
	* by checking if its position exceeds the screen's width and height, considering the character's width and height.
	*
	* @param character Pointer to the character to check.
	* @param screenWidth The width of the screen.
	* @param screenHeight The height of the screen.
	* @return true if the character is out of bounds, false otherwise.
	*/
	bool isOutOfBounds(int xOffset, int yOffset) {
		if (possessedCharacter == nullptr) return true;

		int x = possessedCharacter->getRectPos().x + xOffset;
		int y = possessedCharacter->getRectPos().y + yOffset;
		int width = possessedCharacter->getWidth();
		int height = possessedCharacter->getHeight();

		return x < 0 || y < 0 || x > Screen_Width - width || y > Screen_Height - height;
	}

	void DebugCamera(SDL_Renderer* renderer, SDL_Color color) const
	{
		SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

		// Draw the rectangle outline
		SDL_RenderDrawRect(renderer, &cameraRect);

		// Render the changes to the screen
		SDL_RenderPresent(renderer);
	}

private:
	Camera() { cameraRect = { 0, 0, 100, 100 }; offset = 1; Screen_Width = 0; Screen_Height = 0; }

	// Prevent copying and assignment
	Camera(const Camera&) = delete;
	Camera& operator=(const Camera&) = delete;

	int offset;
	int Screen_Width;
	int Screen_Height;
	SDL_Rect cameraRect;
	std::shared_ptr<GameObject> possessedCharacter;
};

