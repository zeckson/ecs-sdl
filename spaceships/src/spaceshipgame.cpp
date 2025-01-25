//
// Created by Evgenii Shchepotev on 10.04.2024.
//

#include "spaceshipgame.h"

#include "spacescene.h"

SpaceshipGame::SpaceshipGame(const char* title, const Config& config) : SceneGame(title, config) {}

bool SpaceshipGame::onGameCreate() {
  auto scene = std::make_shared<SpaceScene>(*this);
  this->changeScene("space", scene);
  return true;
}

void SpaceshipGame::onKeyEvent(const SDL_Event& event) {}

void SpaceshipGame::onMouseEvent(const SDL_Event& event) {}
