//
// Created by Evgenii Shchepotev on 20.06.2024.
//

#include "playscene.h"
void PlayScene::update() {
  manager.update();

  spawnEnemySystem();
  movementSystem();
  collisionSystem();
  renderSystem();
  lifecycleSystem();
}

void PlayScene::onAction(const Action& action) {

}

void PlayScene::renderSystem() {
  for (const auto& entity : manager.getAllEntities()) {
  }

}
void PlayScene::spawnEnemySystem() {}
void PlayScene::movementSystem() {}
void PlayScene::collisionSystem() {}
void PlayScene::lifecycleSystem() {}
