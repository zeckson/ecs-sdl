//
// Created by Evgenii Shchepotev on 24.01.2025.
//

#ifndef ECS_BALLSCENE_H
#define ECS_BALLSCENE_H

#include <engine/scenegame.h>

#include "scene/playscene.h"
#include "entityconfig.h"
#include "random/randomizer.h"
#include "resource/config.h"

#define ENTITY_BULLET_TAG "bullet"
#define ENTITY_ENEMY_TAG "enemy"
#define ENTITY_PLAYER_TAG "player"

#define MAX_ENEMIES 10

#define BULLET_MINIMUM_FADE 100

class BallScene : public PlayScene {
 private:
  std::shared_ptr<Entity> player;
  Randomizer random;
  EntityConfig config = EntityConfig::loadFromFile("gameofballs/conf/entity.conf");

  Vec2 playerPos{100, 100};
  int currentFrame = 0;

  void spawnEnemySystem();
  void spawnBullet(const Vec2& target);
  void movementSystem();
  void collisionSystem();
  void renderSystem();
  void lifecycleSystem();
  void updatePlayerPosition();
  bool checkScreenCollision(TransformComponent& transform, CollisionComponent& collision) const;

 public:
  BallScene(SceneGame& game);

  void update() override;
  void init() override;
  void onKeyboardAction(const Action& action) override;
  void onMouseAction(const MouseAction& action) override;
};

#endif  // ECS_BallScene_H
