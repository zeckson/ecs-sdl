//
// Created by Evgenii Shchepotev on 24.01.2025.
//

#include "spacescene.h"

#include <assets/sprite.h>
#include <resource/logger.h>

int SPEED = 10;

#include <cmath> // For M_PI

double degreesToRadians(double degrees) {
    return degrees * M_PI / 180.0;
}

void SpaceScene::update() {
  checkBounds();

  game.renderer->renderSprite(player, playerPos);
  currentFrame++;

  if (currentFrame > 120) {
    currentFrame = 0;
  }
}
void SpaceScene::checkBounds() {
  if (playerPos.x > game.width) {
    playerPos.x -= game.width;
  }
  if (playerPos.x <= 0) {
    playerPos.x += game.width;
  }
  if (playerPos.y > game.height) {
    playerPos.y -= game.height;
  }
  if (playerPos.y <= 0) {
    playerPos.y += game.height;
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
  if (player->angle > 360) {
    player->angle -= 360;
  }
  if (player->angle < 0) {
    player->angle += 360;
  }

  int speed = 0;
  if (action.name == "MOVE_UP") {
    speed += SPEED;
  }
  if (action.name == "MOVE_DOWN") {
    speed -= SPEED;
  }
  auto velocity = Util::toVelocity(speed, degreesToRadians(player->angle - 90));
  playerPos += velocity;

  Logger::info("Action[%s] type: %s", action.name.c_str(), action.type == ActionType::START ? "start" : "end");

  Logger::info("Angle: %f, speed: %d", player->angle, speed);
}
