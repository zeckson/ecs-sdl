//
// Created by Evgenii Shchepotev on 30.03.2024.
//

#include "scenegame.h"

void SceneGame::onGameUpdate() {
  getCurrentScene()->update();
}

void SceneGame::onKeyEvent(const SDL_Event& event) {
  getCurrentScene()->handleEvent(event);
}

void SceneGame::onMouseEvent(const SDL_Event& event) {
  getCurrentScene()->handleEvent(event);
}

void SceneGame::changeScene(const std::string& name, const std::shared_ptr<Scene> scene) {
  if (currentScene == name) {
    return;
  }

  std::shared_ptr<Scene>& cScene = scenes[currentScene];
  if (cScene) {
    // TODO: exit action
  }
  if (scene) {
    scenes[name] = scene;
  }
  std::shared_ptr<Scene>& newScene = scenes[name];
  if (!newScene) {
    throw std::runtime_error("Scene not found: " + name);
  }
  currentScene = name;
}
