//
// Created by Evgenii Shchepotev on 28.03.2024.
//

#ifndef ECS_SDL_SCENE_H
#define ECS_SDL_SCENE_H

#include <SDL.h>

#include <map>
#include <memory>
#include <string>

#include "../action/action.h"
#include "../action/keyboardactionhandler.h"
#include "../action/mouseactionhandler.h"

class Scene: public KeyboardActionHandler, public MouseActionHandler {
 public:
  explicit Scene() {};

  virtual void update() = 0;
  virtual void init() = 0;
};

#endif  // ECS_SDL_SCENE_H
