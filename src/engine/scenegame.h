//
// Created by Evgenii Shchepotev on 30.03.2024.
//

#ifndef ECS_SDL_SCENEGAME_H
#define ECS_SDL_SCENEGAME_H

#include <map>
#include <memory>

#include "game.h"

typedef std::map<std::string, std::shared_ptr<Scene>> SceneMap;

class SceneGame : public Game {
 protected:
  void onGameUpdate() override;

  void onKeyEvent(const SDL_Event& event) override;

  void onMouseEvent(const SDL_Event& event) override;

  void changeScene(const std::string& name, const std::shared_ptr<Scene> scene);

 private:
  std::string currentScene;
  SceneMap scenes;
};

#endif  // ECS_SDL_SCENEGAME_H
