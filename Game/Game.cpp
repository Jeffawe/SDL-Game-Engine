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

std::shared_ptr<GameObject> Game::CreateGameObject(int _width, int _height, Vector2 pos, std::string tag, int zIndex)
{
    std::shared_ptr<GameObject> gameObject = std::make_shared<GameObject>(_width, _height, pos, tag, zIndex);
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

    for (const auto& pair : gameObjects) {
        std::shared_ptr<GameObject> gameObject = pair.second;
        gameObject->start();
    }

    return 0;
}

int Game::Update()
{
    // Clear screen
    SDL_RenderClear(gRenderer);

    if (gameObjects.empty()) return 0;

    for (const auto& pair : gameObjects) {
        std::shared_ptr<GameObject> gameObject = pair.second;
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
    for (const auto& pair : gameObjects) {
        std::shared_ptr<GameObject> gameObject = pair.second;
        gameObject->close();
    }

    //Clears all Textures that were added
    TextureManager& textureManager = TextureManager::getInstance();
    textureManager.clear();

    // Close SDL
    closeSDL();
}

std::shared_ptr<GameObject> Game::FindGameObject(std::string stringValue)
{
    for (const auto& pair : gameObjects) {
        if (pair.first.name == stringValue) {
            return pair.second;
        }
    }

    return nullptr;
}

void Game::SetUpGameObjects()
{
    TextureManager& textureManager = TextureManager::getInstance();

    std::shared_ptr<GameObject> player = std::make_shared<Character>(100, 100, Vector2(20, 30), "player", 2);
    if (player) {
        //player->addComponent<Transform>();
        Animator playerAnimator = player->addComponent<Animator>(gRenderer);
        std::filesystem::path folderPath = "./Assets/PlayerAnimations/PlayerIdle/";
        playerAnimator.CreateAnimationState(textureManager.loadTextures(folderPath, gRenderer), "idle");
        playerAnimator.SetInitialState("idle");
    }

    // Create the image GameObject
    std::shared_ptr<GameObject> image = CreateGameObject(50, 50, Vector2(30, 30), "wall", 1);
    if (image) {
        image->addComponent<SpriteComponent>("./Assets/Floor.png", gRenderer);
    }

    // Add the created GameObjects to the gameObjects multimap
    gameObjects.emplace(GameObjectInfo{ 2, "player" }, player);
    //gameObjects.emplace(GameObjectInfo{ 2, "image" }, image);
}

