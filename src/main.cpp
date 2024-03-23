#include <iostream>

#include "base/game.h"
#include "base/config.h"
#include "ballgame.h"
#include "base/logger.h"

int main() {
    BallGame game("The Game Of Balls");

    game.start();

    return 0;
}
