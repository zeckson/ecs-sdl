//
// Created by Evgenii Shchepotev on 28.03.2024.
//

#include "scene.h"

#include "../resource/logger.h"

void Scene::registerAction(const SDL_Scancode code, const std::string& actionName) {
  actionMap[code] = actionName;
}

void Scene::handleEvent(const SDL_Event& event) {
  const auto key = event.key.keysym;

  const auto it = actionMap.find(key.scancode);

  if (it == actionMap.end()) {
    Logger::debug("Action is not registered for event: ", key.scancode);
    return; // Action is not registered for event
  }

  const auto actionName = it->second;

  if (event.type == SDL_KEYDOWN) {
    onAction(Action(actionName, ActionType::START));
  }

  if (event.type == SDL_KEYUP) {
    onAction(Action(actionName, ActionType::END));
  }
}
