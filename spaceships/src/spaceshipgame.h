//
// Created by Evgenii Shchepotev on 10.04.2024.
//

#ifndef ECS_SPACESHIPGAME_H
#define ECS_SPACESHIPGAME_H

#include "engine/game.h"
#include "engine/scenegame.h"

class SpaceshipGame : public SceneGame {
 protected:
  bool onGameCreate() override;

 public:
  SpaceshipGame(const char* title, const Config& config);
};

#endif  // ECS_SPACESHIPGAME_H
