#include <iostream>

#include "base/game.h"
#include "base/config.h"
#include "ballgame.h"
#include "base/logger.h"

#ifndef PROJECT_NAME
#define PROJECT_NAME "SDL Window"
#endif

int main() {
    const auto config = Config::loadFromFile("conf/game.conf");
    printf("Loaded config %ux%u\n", config.gameConfig.width, config.gameConfig.height);

    BallGame game(PROJECT_NAME, config);

    game.start();

    return 0;
}
