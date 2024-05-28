#include "Engine.h"
#include "Game.h"

int finalValue = 0;
bool quit;

int main(int argc, char* argv[]) {
    Game game;
    finalValue = game.Start();

    SDL_Event e;

    // Main loop
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            // User requests quit
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        game.Update();

    }

    game.Close();


    return finalValue;
}


