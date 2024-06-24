//
// Created by Evgenii Shchepotev on 20.06.2024.
//

#ifndef ECS_PLAYSCENE_H
#define ECS_PLAYSCENE_H

#include "entity/entitymanager.h"
#include "scene.h"

class PlayScene : public Scene {
  EntityManager manager;

 public:
  explicit PlayScene() : Scene() {}

  void update() override;

 protected:
  void onAction(const Action& action) override;

 private:
  void spawnEnemySystem();

  void movementSystem();

  void collisionSystem();

  void renderSystem();

  void lifecycleSystem();
};

#endif  // ECS_PLAYSCENE_H
