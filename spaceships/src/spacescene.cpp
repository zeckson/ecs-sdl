//
// Created by Evgenii Shchepotev on 24.01.2025.
//

#include "spacescene.h"

#include <assets/sprite.h>
#include <resource/logger.h>

void SpaceScene::update() {
  game.renderer->renderSprite(player, playerPos);
  currentFrame++;

  if (currentFrame > 120) {
    currentFrame = 0;
  }
}
void SpaceScene::init() {
  player = game.getAssetsManager().getTexture("spaceship");
  registerAction(SDL_SCANCODE_RIGHT, "MOVE_RIGHT");
  registerAction(SDL_SCANCODE_LEFT, "MOVE_LEFT");
  registerAction(SDL_SCANCODE_UP, "MOVE_UP");
  registerAction(SDL_SCANCODE_DOWN, "MOVE_DOWN");
}
void SpaceScene::onAction(const Action& action) {
  if (action.name == "MOVE_RIGHT") {
    player->angle += 15;
  }
  if (action.name == "MOVE_LEFT") {
    player->angle -= 15;
  }
  Logger::info("Action[%s] type: %s", action.name.c_str(), action.type == ActionType::START ? "start" : "end");
}
