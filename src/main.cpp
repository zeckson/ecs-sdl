#include <SDL2/SDL.h>
#include <iostream>

#include "game.h"
#include "ballgame.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#ifndef PROJECT_NAME
#define PROJECT_NAME "SDL Window"
#endif

int main() {
    BallGame game(PROJECT_NAME, SCREEN_WIDTH, SCREEN_HEIGHT);

    game.start();

    return 0;
}
