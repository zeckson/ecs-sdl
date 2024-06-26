//
// Created by Evgenii Shchepotev on 30.03.2024.
//

#ifndef ECS_SDL_SCENEGAME_H
#define ECS_SDL_SCENEGAME_H

#include <map>
#include <memory>

#include "../engine/game.h"
#include "scene.h"

typedef std::map<std::string, std::shared_ptr<Scene>> SceneMap;

class SceneGame : public Game {
  std::string currentScene;
  SceneMap scenes;

 protected:
  void onGameUpdate() override;

  void onKeyEvent(const SDL_Event& event) override;

  void onMouseEvent(const SDL_Event& event) override;

  void changeScene(const std::string& name, const std::shared_ptr<Scene> scene);

 private:
  std::shared_ptr<Scene> getCurrentScene() { return scenes[currentScene]; }
};

#endif  // ECS_SDL_SCENEGAME_H
