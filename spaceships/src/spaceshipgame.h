//
// Created by Evgenii Shchepotev on 10.04.2024.
//

#ifndef ECS_SPACESHIPGAME_H
#define ECS_SPACESHIPGAME_H

#include "engine/game.h"
#include "scene/scenegame.h"

class SpaceshipGame : public SceneGame {
 public:
 private:
  bool onGameCreate() override;

  void onGameUpdate() override;

 protected:
  void onKeyEvent(const SDL_Event& event) override;

  void onMouseEvent(const SDL_Event& event) override;

 public:
  SpaceshipGame(const char* title, const Config& config);
};

#endif  // ECS_SPACESHIPGAME_H
