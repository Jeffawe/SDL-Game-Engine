#include "Game.h"

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

std::shared_ptr<GameObject> Game::CreateGameObject(int _width, int _height, int _x, int _y)
{
    std::shared_ptr<GameObject> gameObject = std::make_shared<GameObject>(_width, _height, _x, _y);
    return gameObject;
}

int Game::Start()
{
    // Initialize SDL
    if (!initSDL()) {
        printf("Failed to initialize SDL!\n");
        return -1;
    }

    SetUpGameObjects();

    if (gameObjects.empty()) return 0;

    for (const auto& gameObject : gameObjects) {
        gameObject->start();
    }

    return 0;
}

int Game::Update()
{
    // Clear screen
    SDL_RenderClear(gRenderer);

    if (gameObjects.empty()) return 0;

    for (const auto& gameObject : gameObjects) {
        gameObject->update();
    }

    // Update screen
    SDL_RenderPresent(gRenderer);

    // Calculate frame time and delay if necessary to achieve desired FPS
    frameTime = SDL_GetTicks() - frameStart; // Calculate time taken to process the frame
    if (frameTime < FRAME_DELAY) {
        SDL_Delay(FRAME_DELAY - frameTime); // Delay if the frame was processed too quickly
    }

    return 0;
}

void Game::Close()
{
    for (const auto& gameObject : gameObjects) {
        gameObject->close();
    }

    //Clears all Textures that were added
    TextureManager& textureManager = TextureManager::getInstance();
    textureManager.clear();

    // Close SDL
    closeSDL();
}

void Game::SetUpGameObjects()
{
    //Character player = Character();
    //gameObjects.push_back(std::make_unique<GameObject>(std::move(player)));

    // Create a GameObject
    std::shared_ptr<GameObject> image = CreateGameObject(50, 50, 30, 30);

    //Add the Sprite Component to it
    image->addComponent<SpriteComponent>("./Assets/Floor.png", gRenderer);
    gameObjects.push_back(image);
}

