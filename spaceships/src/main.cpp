#include "resource/config.h"
#include "spaceshipgame.h"

int main() {
  SpaceshipGame game("Spaceships", Config::loadFromFile("spaceships/conf/game.conf"));

  game.start();

  return 0;
}
