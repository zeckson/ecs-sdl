//
// Created by Evgenii Shchepotev on 14.03.2024.
//

#include "ballgame.h"

#include <cmath>
#include <memory>

#include "resource/logger.h"

bool BallGame::onGameCreate() {
  player = manager.createEntity(ENTITY_PLAYER_TAG);
  const auto playerConfig = config.player;
  player->addComponent<ShapeComponent>(playerConfig.shapeRadius, playerConfig.outlineColor, playerConfig.fillColor,
                                       playerConfig.thickness);
  player->addComponent<CollisionComponent>(playerConfig.collisionRadius);
  auto center = Vec2(width / 2, height / 2);
  player->addComponent<TransformComponent>(center, 0, 0);
  player->addComponent<InputComponent>();
  return true;
}

void BallGame::spawnEnemySystem() {
  const auto& enemyConfig = config.enemy;
  if (frameRate.currentFrame() % enemyConfig.spawnInterval == 0 && manager.getAllEntities().size() < MAX_ENEMIES) {
    const std::string name = ENTITY_ENEMY_TAG;
    auto enemy = manager.createEntity(name);
    const int radius = random.between(enemyConfig.shapeRadius.first, enemyConfig.shapeRadius.second) * 10;
    const int collisionRadius = radius - enemyConfig.thickness;
    enemy->addComponent<CollisionComponent>(collisionRadius);
    enemy->addComponent<ShapeComponent>(radius, enemyConfig.outlineColor, BLACK, enemyConfig.thickness);
    int startX = random.between(radius, width - radius);
    int startY = random.between(radius, height - radius);
    auto center = Vec2(startX, startY);
    double direction = random.get(1.0f) * M_2_PI;
    const auto speed = random.betweenf(enemyConfig.speed.first, enemyConfig.speed.second);
    enemy->addComponent<TransformComponent>(center, speed, direction);
    Logger::info("Entity[%s] created at: [%d, %d] with radius: %d", name.c_str(), startX, startY, radius);
  }
}

void BallGame::spawnBullet(const Vec2& target) {
  const std::string name = ENTITY_BULLET_TAG;
  auto bullet = manager.createEntity(name);
  const auto& bulletConfig = config.bullet;
  int radius = 5;
  bullet->addComponent<CollisionComponent>(bulletConfig.collisionRadius);
  bullet->addComponent<ShapeComponent>(bulletConfig.shapeRadius, bulletConfig.outlineColor, bulletConfig.fillColor,
                                       bulletConfig.thickness);
  const auto playerPosition = player->getComponent<TransformComponent>().position;
  auto distance = target - playerPosition;
  auto velocity = distance.normalize();
  bullet->addComponent<TransformComponent>(playerPosition, velocity * bulletConfig.speed);
  bullet->addComponent<LifecycleComponent>(bulletConfig.lifespan);
  Logger::info("Entity[%s] created at: %s with radius: %d", name.c_str(), playerPosition.toString().c_str(), radius);
}

void BallGame::onGameUpdate() {
  manager.update();

  spawnEnemySystem();
  movementSystem();
  collisionSystem();
  renderSystem();
  lifecycleSystem();
}

void BallGame::movementSystem() {
  for (const auto& entity : manager.getAllEntities()) {
    if (entity->has<TransformComponent>()) {
      auto& transform = entity->getComponent<TransformComponent>();
      transform.position.x += std::round(transform.velocity.x);
      transform.position.y += std::round(transform.velocity.y);
    }
    if (entity == player) {
      updatePlayerPosition();
    }
  }
}

void BallGame::collisionSystem() {
  for (const auto& entity : manager.getAllEntities()) {
    if (entity->has<TransformComponent>() && entity->has<CollisionComponent>()) {
      auto& transform = entity->getComponent<TransformComponent>();
      auto& collision = entity->getComponent<CollisionComponent>();
      const bool collide = checkScreenCollision(transform, collision);
      if (collide) {
        Logger::debug("Wall collision: [%s]:%s", entity->tag().c_str(), transform.position.toString().c_str());
        if (entity->tag() == ENTITY_BULLET_TAG) {
          manager.removeEntity(entity);
        }
      }
    }
  }

  const auto& enemyList = manager.getEntities(ENTITY_ENEMY_TAG);
  const auto& bulletList = manager.getEntities(ENTITY_BULLET_TAG);

  // TODO: try to get rid of excessive memory copy
  const auto enemyVector = std::vector(enemyList.begin(), enemyList.end());
  for (int i = 0; i < enemyVector.size(); ++i) {
    const auto& enemy = enemyVector[i];

    // enemy - player collision
    if (collides(player, enemy)) {
      manager.removeEntity(enemy);
      player->getComponent<TransformComponent>().position = Vec2(width / 2, height / 2);

      goto endloop;  // we don't care about collision enemy is dead
    }

    // enemy - bullet collision
    for (const auto& bullet : bulletList) {
      if (collides(bullet, enemy)) {
        manager.removeEntity(enemy);
        manager.removeEntity(bullet);

        goto endloop;  // we don't care about collision enemy is dead
      }
    }

    // enemy - enemy collision
    for (int j = i + 1; j < enemyVector.size(); ++j) {
      const auto& otherEnemy = enemyVector[j];

      if (collides(enemy, otherEnemy)) {
        // Circles collide, reverse velocities
        Vec2 enemyVelocity = enemy->getComponent<TransformComponent>().velocity;
        enemy->getComponent<TransformComponent>().velocity = otherEnemy->getComponent<TransformComponent>().velocity;
        otherEnemy->getComponent<TransformComponent>().velocity = enemyVelocity;

        // TODO: resolve collision overlapping (circles can attach or stick together)
      }
    }
  endloop:;
  }
}

bool BallGame::collides(const std::shared_ptr<Entity>& source, const std::shared_ptr<Entity>& target) {
  if (!(source->has<CollisionComponent>() && target->has<CollisionComponent>())) {
    return false;
  }

  if (!(source->has<TransformComponent>() && target->has<TransformComponent>())) {
    return false;
  }
  const auto& sourceTransform = source->getComponent<TransformComponent>();
  const auto& targetTransform = target->getComponent<TransformComponent>();

  const auto& sourceCollision = source->getComponent<CollisionComponent>();
  const auto& targetCollision = target->getComponent<CollisionComponent>();

  const auto& left = sourceTransform.position;
  const auto& right = targetTransform.position;
  float dx = left.x - right.x;
  float dy = left.y - right.y;
  float distance = dx * dx + dy * dy;

  int minDistance =
      (sourceCollision.radius + targetCollision.radius) * (sourceCollision.radius + targetCollision.radius);
  const auto collided = distance < float(minDistance);
  if (collided) {
    Logger::debug("Entity collision: [%s]:%s and [%s]:%s", source->tag().c_str(), left.toString().c_str(),
                  target->tag().c_str(), right.toString().c_str());
  }
  return collided;
}

void BallGame::lifecycleSystem() {
  for (const auto& entity : manager.getAllEntities()) {
    if (entity->has<LifecycleComponent>()) {
      auto& lifecycle = entity->getComponent<LifecycleComponent>();
      lifecycle.framesLeft--;
      if (lifecycle.framesLeft < 0) {
        manager.removeEntity(entity);
      }
    }
  }
}

bool BallGame::checkScreenCollision(TransformComponent& transform, CollisionComponent& collision) const {
  Vec2& velocity = transform.velocity;
  Vec2& position = transform.position;
  float x = position.x;
  float y = position.y;

  bool collide = false;

  Uint32 radius = collision.radius;
  float right = width - radius;
  float left = 0 + radius;
  if (x > right) {
    velocity.x *= -1.0;
    position.x = right;
    collide = true;
  }
  if (x < left) {
    velocity.x *= -1.0;
    position.x = left;
    collide = true;
  }
  Uint32 bottom = height - radius;
  Uint32 top = 0 + radius;
  if (y > bottom) {
    velocity.y *= -1.0;
    position.y = bottom;
    collide = true;
  }
  if (y < top) {
    velocity.y *= -1.0;
    position.y = top;
    collide = true;
  }
  return collide;
}

void BallGame::renderSystem() {
  for (const auto& entity : manager.getAllEntities()) {
    if (entity->has<ShapeComponent>()) {
      auto& shape = entity->getComponent<ShapeComponent>();

      if (entity->has<LifecycleComponent>()) {
        const auto& lifecycle = entity->getComponent<LifecycleComponent>();
        const auto step = (SDL_ALPHA_OPAQUE - BULLET_MINIMUM_FADE) / lifecycle.framesToLive;
        const auto opacity = lifecycle.framesLeft * step + BULLET_MINIMUM_FADE;

        // NB! Since SDL2 doesn't support alpha channel on screen rendering
        // Imitate it by blending with background
        // TODO: use correct color from config
        const auto& fade = Pixel(opacity, opacity, opacity);
        shape.circle.setFillColor(fade);
        shape.circle.setOutlineColor(fade);
      }

      if (entity->has<TransformComponent>()) {
        const auto& transform = entity->getComponent<TransformComponent>();
        shape.circle.draw(renderer, transform.position);
      }
    }
  }
}

void BallGame::updatePlayerPosition() {
  const auto& input = player->getComponent<InputComponent>();
  auto& transform = player->getComponent<TransformComponent>();

  float yAxisMove = 0;
  if (input.isset(Direction::UP)) yAxisMove -= 1;
  if (input.isset(Direction::DOWN)) yAxisMove += 1;

  float xAxisMove = 0;
  if (input.isset(Direction::LEFT)) xAxisMove -= 1;
  if (input.isset(Direction::RIGHT)) xAxisMove += 1;

  const Vec2& velocity = Vec2{xAxisMove, yAxisMove}.normalize() * config.player.speed;
  transform.position += velocity;
}

void BallGame::onKeyEvent(const SDL_Event& event) {
  const auto key = event.key.keysym;

  for (const auto& entity : manager.getAllEntities()) {
    if (entity->has<InputComponent>()) {
      auto& input = entity->getComponent<InputComponent>();
      if (event.type == SDL_KEYDOWN) {
        switch (key.scancode) {
          case SDL_SCANCODE_UP:
            input.set(Direction::UP);
            break;
          case SDL_SCANCODE_DOWN:
            input.set(Direction::DOWN);
            break;
          case SDL_SCANCODE_LEFT:
            input.set(Direction::LEFT);
            break;
          case SDL_SCANCODE_RIGHT:
            input.set(Direction::RIGHT);
            break;
          default:
            // do nothing
            break;
        }
      }
      if (event.type == SDL_KEYUP) {
        switch (key.scancode) {
          case SDL_SCANCODE_UP:
            input.unset(Direction::UP);
            break;
          case SDL_SCANCODE_DOWN:
            input.unset(Direction::DOWN);
            break;
          case SDL_SCANCODE_LEFT:
            input.unset(Direction::LEFT);
            break;
          case SDL_SCANCODE_RIGHT:
            input.unset(Direction::RIGHT);
            break;
          default:
            // do nothing
            break;
        }
      }
    }
  }
}

void BallGame::onMouseEvent(const SDL_Event& event) {
  if (event.type == SDL_MOUSEBUTTONDOWN) {
    if (event.button.button == SDL_BUTTON_LEFT) {
      int mouseX, mouseY;
      SDL_GetMouseState(&mouseX, &mouseY);
      Logger::info("Left mouse button clicked at: [%u, %u]", mouseX, mouseY);
      spawnBullet(Vec2(mouseX, mouseY));
    }
  }
}
