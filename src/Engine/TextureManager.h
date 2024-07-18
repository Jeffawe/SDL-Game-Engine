#pragma once

#include <unordered_map>
#include <memory>
#include <unordered_map>
#include <SDL.h>
#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include "../EngineValues.h"

namespace fs = std::filesystem;

class TextureManager {
public:
    static TextureManager& getInstance() {
        static TextureManager instance;
        return instance;
    }

    // Load a texture from a file
    SDL_Texture* loadTexture(const std::string& fileName, SDL_Renderer* renderer, bool cache = true);

    std::vector<SDL_Texture*> loadTextures(const fs::path& folderName, SDL_Renderer* renderer, bool cache = true);

    // Clean up all textures
    void clear();

private:
    TextureManager() {};

    ~TextureManager() { clear(); }

    // Disable copy constructor and assignment operator
    TextureManager(const TextureManager&) = delete;
    TextureManager& operator=(const TextureManager&) = delete;

    // Map to store cached textures with custom deleter
    std::unordered_map<std::string, std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)>> textures;
};

