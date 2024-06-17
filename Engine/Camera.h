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

    SDL_Rect cameraRect;
    std::shared_ptr<GameObject> possessedCharacter;

    // Convert world coordinates to screen coordinates
    Vector2 worldToScreen(const Vector2& worldPos, const std::string& tag) const {
        if (possessedCharacter && tag != "RUN") {
            return worldPos - Vector2(cameraRect.x, cameraRect.y);
        }

        return worldPos;
    }

    void Possess(std::shared_ptr<GameObject> _possessedCharacter) {
        possessedCharacter = _possessedCharacter;
    }

    void updateRect() {
        if (possessedCharacter != nullptr) {
            cameraRect.x = possessedCharacter->getPos().x - cameraRect.w / 2;
            cameraRect.y = possessedCharacter->getPos().y - cameraRect.h / 2;

            if (cameraRect.x < 0) cameraRect.x = 0;
            if (cameraRect.y < 0) cameraRect.y = 0;
            if (cameraRect.x > cameraRect.w) cameraRect.x = cameraRect.w;
            if (cameraRect.y > cameraRect.h) cameraRect.y = cameraRect.h;
        }
    }

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

    void DebugCamera(SDL_Renderer* renderer, SDL_Color color) const
    {
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

        // Draw the rectangle outline
        SDL_RenderDrawRect(renderer, &cameraRect);

        // Render the changes to the screen
        SDL_RenderPresent(renderer);
    }

private:
    Camera() { cameraRect = { 0, 0, 100, 100 }; offset = 1; }

    // Prevent copying and assignment
    Camera(const Camera&) = delete;
    Camera& operator=(const Camera&) = delete;

    int offset;
};

