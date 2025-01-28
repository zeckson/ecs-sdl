//
// Created by Evgenii Shchepotev on 30.03.2024.
//

#ifndef ECS_SDL_SCENEGAME_H
#define ECS_SDL_SCENEGAME_H

#include <map>
#include <memory>

#include "../scene/scene.h"
#include "game.h"

class SceneGame : public Game {
  using ScenePointer = std::shared_ptr<Scene<SceneGame>>;
  using SceneMap = std::map<std::string, ScenePointer>;

 private:
  ScenePointer getCurrentScene() { return scenes[currentScene]; }
  std::string currentScene;
  SceneMap scenes;

 protected:
  explicit SceneGame(const char* title, const Config& config) : Game(title, config) {}

  void onGameUpdate() override;

  void onKeyEvent(const SDL_Event& event) override;

  void onMouseEvent(const SDL_Event& event) override;

  void registerScene(const std::string& name, const ScenePointer& scene);

 public:
  void changeScene(const std::string& name);
};

#endif  // ECS_SDL_SCENEGAME_H
