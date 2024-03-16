#include <SDL2/SDL.h>
#include <iostream>

#include "base/game.h"
#include "ballgame.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#ifndef PROJECT_NAME
#define PROJECT_NAME "SDL Window"
#endif

int main() {
    BallGame game(PROJECT_NAME, SCREEN_WIDTH, SCREEN_HEIGHT);

    game.start();

    return 0;
}
