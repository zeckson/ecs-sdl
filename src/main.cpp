#include <SDL2/SDL.h>
#include <iostream>

#include "game.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#ifndef PROJECT_NAME
#define PROJECT_NAME "SDL Window"
#endif

class ECSDemoGame: public Game {
public:
    ECSDemoGame(): Game(PROJECT_NAME, SCREEN_WIDTH, SCREEN_HEIGHT) {}

    bool onGameCreate() override {
        return true;
    }

    bool onGameUpdate(double elapsedTime) override {
        renderer->setColor(RED);
        renderer->drawCircle(width / 2, height / 2, std::min(width, height) / 4);
        return true;
    }

    void onKeyDown(const SDL_Keysym &keysym) override {
    }
};

int main() {
    ECSDemoGame game;

    game.start();

    return 0;
}
