//
// Created by Evgenii Shchepotev on 20.06.2024.
//

#ifndef ECS_PLAYSCENE_H
#define ECS_PLAYSCENE_H

#include "entity/entitymanager.h"
#include "scene.h"
#include <engine/scenegame.h>

class PlayScene : public Scene<SceneGame> {
 public:
  explicit PlayScene(SceneGame& game) : Scene(game) {}

  void update() override;

 protected:
  EntityManager manager;
  void onKeyboardAction(const Action& action) override;

 private:
  void spawnEnemySystem();

  void movementSystem();

  void collisionSystem();

  void renderSystem();

  void lifecycleSystem();
};

#endif  // ECS_PLAYSCENE_H
