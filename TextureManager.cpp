#include "TextureManager.h"

SDL_Texture* TextureManager::loadTexture(const std::string& fileName, SDL_Renderer* renderer, bool cache)
{
    if (cache) {
        // Check if the texture is already in the cache
        auto it = textures.find(fileName);
        if (it != textures.end()) {
            // Texture found, return it
            return it->second.get();
        }
    }

    // Load the texture
    SDL_Texture* texture = IMG_LoadTexture(renderer, fileName.c_str());
    if (texture) {
        if (cache) {
            // Cache the texture with custom deleter
            textures.emplace(fileName, std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)>(texture, SDL_DestroyTexture));
        }
        return texture;
    }
    else {
        std::cerr << "Failed to load texture: " << fileName << " - " << IMG_GetError() << std::endl;
        return nullptr;
    }
}

void TextureManager::clear()
{
    textures.clear();
}
