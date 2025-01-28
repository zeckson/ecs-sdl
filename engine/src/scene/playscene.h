//
// Created by Evgenii Shchepotev on 20.06.2024.
//

#ifndef ECS_PLAYSCENE_H
#define ECS_PLAYSCENE_H

#include "entity/entitymanager.h"
#include "scene.h"

class PlayScene : public Scene {
 public:
  explicit PlayScene(Game& game) : Scene(game) {}

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
