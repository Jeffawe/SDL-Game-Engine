#pragma once

#include <SDL.h>
#include <iostream> 

#include "Component.h"
#include "TextureManager.h"
#include "GameObject.h"

/// @brief A component that handles sprite rendering.
/// @param spritePath: The file path to the sprite image.
/// @param renderer: The SDL renderer.
class SpriteComponent : public Component {
private:
    SDL_Texture* sprite;
    SDL_Renderer* renderer;

public:
    SpriteComponent(const std::string& spritePath, SDL_Renderer* _renderer){
        TextureManager& textureManager = TextureManager::getInstance();
        renderer = _renderer;
        sprite = textureManager.loadTexture(spritePath, _renderer, true); 
    }

    void start() override {}

    //Called On Update
    void update() override {
        if (owner != nullptr) {
            owner->ChangeDestRect();
            SDL_RenderCopy(renderer, sprite, NULL, &owner->destRect);
        }        
    }

    //Called on render
    void render() override {}

    void close() override {
        renderer = nullptr;
        sprite = nullptr;
    }
};