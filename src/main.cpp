#include <iostream>

#include "engine/game.h"
#include "resource/config.h"
#include "gameofballs/ballgame.h"
#include "resource/logger.h"

int main() {
    BallGame game("The Game Of Balls");

    game.start();

    return 0;
}
