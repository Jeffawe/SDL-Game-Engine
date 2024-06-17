#include "TestGame.h"

const TileBase tilemap1 = TileBase({
    {0, 1, 0, 0, 0, 0, 0, 0},
    {1, 1, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 1, 0, 0, 0, 0}
});

const TileBase tilemap2 = TileBase({
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
});

std::vector<TileBase> tilemaps = { tilemap1, tilemap2 };

int TestGame::Start()
{
    Game::Start();
    TextureManager& textureManager = TextureManager::getInstance();
    InputManager& inputManager = InputManager::getInstance();


    player = std::make_shared<Character>(50, 50, Vector2(0, 5), "player");
    if (player) {
        Transform& transform = player->addComponent<Transform>();
        Collider& collider = player->addComponent<Collider>();
        collider.SetColliderSize(30, 30);
        transform.SetSpeed(5);
        Animator& playerAnimator = player->addComponent<Animator>(gRenderer, 5);
        std::filesystem::path folderPath = "./Assets/PlayerAnimations/PlayerIdle/";
        playerAnimator.CreateAnimationState(textureManager.loadTextures(folderPath, gRenderer), "idle");
        playerAnimator.SetInitialState("idle");
    }

    inputManager.Possess(player);
    camera->Possess(player);

    tilemap->CreateNewTile(1, textureManager.loadTexture("./Assets/Floor.png", gRenderer), true);
    tilemap->GenerateTileMap(tilemaps, SCREEN_WIDTH, SCREEN_HEIGHT, 100, gRenderer);

    // Add the created GameObjects to the gameObjects multimap
    gameObjects.emplace(GameObjectInfo{ 2, "player" }, player);

    return 0;
}

int TestGame::Update()
{
    Game::Update();
    SDL_Color red = { 255, 0, 0, 255 };
    camera->DebugCamera(gRenderer, red);
    DebugRect(gRenderer, FindGameObject(2, "player")->getComponent<Collider>()->GetBoundingBox(), red);
    //tilemap->DebugCollisions(gRenderer, red);
    return 0;
}
