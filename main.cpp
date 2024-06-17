#include "Engine.h"
#include "./TestGame.h"

int finalValue = 0;
bool quit;

int main(int argc, char* argv[]) {
    TestGame game;
    finalValue = game.Start();

    SDL_Event e;
    InputManager& inputManager = InputManager::getInstance();

    // Main loop
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            // User requests quit
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            else {
                inputManager.Input(e);
            }
        }

        game.Update();
    }

    game.Close();

    return finalValue;
}


