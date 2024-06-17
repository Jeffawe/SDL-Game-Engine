#include "Game.h"
#include "../Engine.h"

bool Game::initSDL()
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    // Create window
    gWindow = SDL_CreateWindow("2D Top-Down Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    // Create renderer
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (gRenderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    // Set renderer color
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

    // Allows for (Initializes) Image Loading abilities using SDL_image library
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        return false;
    }

    return true;
}

void Game::closeSDL()
{
    // Destroy window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    // Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

int Game::Start()
{
    // Initialize SDL
    if (!initSDL()) {
        printf("Failed to initialize SDL!\n");
        return -1;
    }
    
    camera = &Camera::getInstance();
    tilemap = &Tilemap::getInstance();

    camera->cameraRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

    if (gameObjects.empty()) return 0;

    for (const auto& pair : gameObjects) {
        std::shared_ptr<GameObject> gameObject = pair.second;
        gameObject->start();
    }

    return 0;
}

int Game::Update()
{
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);

    // Clear screen
    SDL_RenderClear(gRenderer);

    if (gameObjects.empty()) return 0;

    camera->updateRect();
    tilemap->Update();

    for (const auto& pair : gameObjects) {
        std::shared_ptr<GameObject> gameObject = pair.second;
        gameObject->update();
    }

    // Update screen
    SDL_RenderPresent(gRenderer);

    return 0;
}

void Game::Close()
{
    for (const auto& pair : gameObjects) {
        std::shared_ptr<GameObject> gameObject = pair.second;
        gameObject->close();
    }

    //Clears all Textures that were added
    TextureManager& textureManager = TextureManager::getInstance();
    textureManager.clear();
    if (tilemap != nullptr) tilemap->Close();

    // Close SDL
    closeSDL();
}

void Game::DebugRect(SDL_Renderer* renderer, SDL_Rect* rect, SDL_Color color)
{
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

        // Draw the rectangle outline
        SDL_RenderDrawRect(renderer, rect);

        // Render the changes to the screen
        SDL_RenderPresent(renderer);
}

std::shared_ptr<GameObject> Game::FindGameObject(int zIndex, std::string name)
{
    GameObjectInfo info{ zIndex, name };
    auto range = gameObjects.equal_range(info);

    for (auto it = range.first; it != range.second; ++it) {
        if (it->first.name == name) {
            return it->second;
        }
    }

    return nullptr;
}

