//
// Created by Evgenii Shchepotev on 10.04.2024.
//

#include "spaceshipgame.h"

#include "spacescene.h"

SpaceshipGame::SpaceshipGame(const char* title, const Config& config) : SceneGame(title, config) {
  auto scene = std::make_shared<SpaceScene>();
  this->changeScene("space", scene);
}

bool SpaceshipGame::onGameCreate() { return true; }

void SpaceshipGame::onGameUpdate() {
  const std::unique_ptr<Sprite>& sprite = getAssetsManager().getTexture("spaceship");
  renderer->renderSprite(sprite, {100, 100});
}

void SpaceshipGame::onKeyEvent(const SDL_Event& event) {}

void SpaceshipGame::onMouseEvent(const SDL_Event& event) {}
