//
// Created by Evgenii Shchepotev on 14.03.2024.
//

#ifndef ECS_SDL_BALLGAME_H
#define ECS_SDL_BALLGAME_H

#include "scene/scenegame.h"

class BallGame : public SceneGame {
 public:
  explicit BallGame(const char* title) : SceneGame(title, Config::loadFromFile("gameofballs/conf/game.conf")) {}

 protected:
  bool onGameCreate() override;
};

#endif  // ECS_SDL_BALLGAME_H
