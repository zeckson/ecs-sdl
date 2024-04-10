#include <iostream>

#include "engine/game.h"
#include "resource/config.h"
#include "gameofballs/ballgame.h"
#include "resource/logger.h"
#include "spaceships/spaceshipgame.h"

//int main() {
//    BallGame game("The Game Of Balls");
//
//    game.start();
//
//    return 0;
//}

int main() {
    SpaceshipGame game("Spaceships", Config::loadFromFile("conf/game.conf"));

    game.start();

    return 0;
}
