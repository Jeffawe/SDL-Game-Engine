#include "TextureManager.h"
#include <SDL_image.h>

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

std::vector<SDL_Texture*> TextureManager::loadTextures(const fs::path& folderPath, SDL_Renderer* renderer, bool cache)
{
    std::vector<SDL_Texture*> textures;
    try {
        for (const auto& entry : fs::directory_iterator{ folderPath.c_str() }) {
            if (fs::is_regular_file(entry)) {
                auto extension = toLower(entry.path().extension().string());
                if (extension == ".png" || extension == ".jpeg" || extension == ".jpg") {
                    SDL_Texture* texture = loadTexture(entry.path().string(), renderer, cache);
                    if (texture != nullptr) {
                        textures.push_back(texture);
                    }
                    else {
                        std::cerr << "Image is Null" << std::endl;
                    }
                }
            }
        }
    }
    catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
    }

    return textures;
}

void TextureManager::clear()
{
    textures.clear();
}
