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

class Scene {
  std::map<SDL_Scancode, std::string> actionMap;

 public:
  explicit Scene() {};

  void handleEvent(const SDL_Event& event);

  virtual void update() = 0;
  virtual void init() = 0;

 protected:
  void registerAction(const SDL_Scancode code, const std::string& actionName);

  virtual void onAction(const Action& action) = 0;
};

#endif  // ECS_SDL_SCENE_H
