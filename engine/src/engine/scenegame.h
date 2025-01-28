//
// Created by Evgenii Shchepotev on 30.03.2024.
//

#ifndef ECS_SDL_SCENEGAME_H
#define ECS_SDL_SCENEGAME_H

#include <map>
#include <memory>

#include "../scene/scene.h"
#include "game.h"

typedef std::map<std::string, std::shared_ptr<Scene>> SceneMap;

class SceneGame : public Game {
  std::string currentScene;
  SceneMap scenes;

 protected:
  explicit SceneGame(const char* title, const Config& config) : Game(title, config) {}

  void onGameUpdate() override;

  void onKeyEvent(const SDL_Event& event) override;

  void onMouseEvent(const SDL_Event& event) override;

  void changeScene(const std::string& name);

  void registerScene(const std::string& name, const std::shared_ptr<Scene>& scene);

 private:
  std::shared_ptr<Scene> getCurrentScene() { return scenes[currentScene]; }
};

#endif  // ECS_SDL_SCENEGAME_H
