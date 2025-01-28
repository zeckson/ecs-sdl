//
// Created by Evgenii Shchepotev on 30.03.2024.
//

#include "scenegame.h"

void SceneGame::onGameUpdate() { getCurrentScene()->update(); }

void SceneGame::onKeyEvent(const SDL_Event& event) { getCurrentScene()->handleKeyboardEvent(event); }

void SceneGame::onMouseEvent(const SDL_Event& event) { getCurrentScene()->handleMouseEvent(event); }

void SceneGame::registerScene(const std::string& name, const ScenePointer& scene) {
  scene->init();
  scenes[name] = scene;
}

void SceneGame::changeScene(const std::string& name) {
  if (currentScene == name) {
    return;
  }

  ScenePointer& cScene = scenes[currentScene];
  if (cScene) {
    // TODO: exit action
  }
  auto scene = scenes.find(name);
  if (scene == scenes.end()) {
    throw std::runtime_error("Scene is not registerd for name: " + name);
  }
  const auto& newScene = scene->second;

  currentScene = name;
}
