//
// Created by Evgenii Shchepotev on 10.04.2024.
//

#include "spaceshipgame.h"

#include "spacescene.h"

SpaceshipGame::SpaceshipGame(const char* title, const Config& config) : SceneGame(title, config) {}

bool SpaceshipGame::onGameCreate() {
  registerScene("space", std::make_shared<SpaceScene>(SpaceScene(*this)));
  this->changeScene("space");
  return true;
}
