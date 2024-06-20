//
// Created by Evgenii Shchepotev on 28.03.2024.
//

#ifndef ECS_SDL_SCENE_H
#define ECS_SDL_SCENE_H

#include <SDL.h>

#include <map>
#include <string>

#include "../action/action.h"

class Scene {
 public:
  explicit Scene() {};
  void handleEvent(const SDL_Event& event);
  void virtual update() = 0;
 protected:
  void registerAction(const SDL_Scancode code, const std::string& actionName);
  void virtual init() = 0;
  void virtual onAction(const Action& action) = 0;
 private:
  std::map<SDL_Scancode, std::string> actionMap;
};

#endif  // ECS_SDL_SCENE_H
