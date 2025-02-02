//
// Created by Evgenii Shchepotev on 24.01.2025.
//

#include "ballscene.h"

#include <resource/logger.h>

bool collides(const std::shared_ptr<Entity>& source, const std::shared_ptr<Entity>& target) {
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

BallScene::BallScene(SceneGame& game) : PlayScene(game) {}

void BallScene::init() {
  registerKeyboardAction(SDL_SCANCODE_RIGHT, "MOVE_RIGHT");
  registerKeyboardAction(SDL_SCANCODE_LEFT, "MOVE_LEFT");
  registerKeyboardAction(SDL_SCANCODE_UP, "MOVE_UP");
  registerKeyboardAction(SDL_SCANCODE_DOWN, "MOVE_DOWN");

  registerMouseAction(MouseActionType::MOUSE_LEFT_CLICK, "SHOOT");

  player = manager.createEntity(ENTITY_PLAYER_TAG);
  const auto playerConfig = config.player;
  player->addComponent<ShapeComponent>(playerConfig.shapeRadius, playerConfig.outlineColor, playerConfig.fillColor,
                                       playerConfig.thickness);
  player->addComponent<CollisionComponent>(playerConfig.collisionRadius);
  auto center = Vec2(game.width / 2, game.height / 2);
  player->addComponent<TransformComponent>(center, 0, 0);
  player->addComponent<InputComponent>();
}

void BallScene::update() {
  manager.update();

  spawnEnemySystem();
  movementSystem();
  collisionSystem();
  renderSystem();
  lifecycleSystem();
}

void BallScene::onKeyboardAction(const Action& action) {
  const auto& entity = player;

  if (entity->has<InputComponent>()) {
    auto& input = entity->getComponent<InputComponent>();
    if (action.name == "MOVE_RIGHT") {
      action.type == ActionType::START ? input.set(Direction::RIGHT) : input.unset(Direction::RIGHT);
    }
    if (action.name == "MOVE_LEFT") {
      action.type == ActionType::START ? input.set(Direction::LEFT) : input.unset(Direction::LEFT);
    }
    if (action.name == "MOVE_UP") {
      action.type == ActionType::START ? input.set(Direction::UP) : input.unset(Direction::UP);
    }
    if (action.name == "MOVE_DOWN") {
      action.type == ActionType::START ? input.set(Direction::DOWN) : input.unset(Direction::DOWN);
    }
  }
}

void BallScene::onMouseAction(const MouseAction& action) {
  if (action.name == "SHOOT" && action.type == ActionType::END) {
    spawnBullet(action.position);
  }
}

void BallScene::spawnBullet(const Vec2& target) {
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

void BallScene::spawnEnemySystem() {
  const auto& enemyConfig = config.enemy;
  if (game.frameRate.currentFrame() % enemyConfig.spawnInterval == 0 && manager.getAllEntities().size() < MAX_ENEMIES) {
    const std::string name = ENTITY_ENEMY_TAG;
    auto enemy = manager.createEntity(name);
    const int radius = random.between(enemyConfig.shapeRadius.first, enemyConfig.shapeRadius.second) * 10;
    const int collisionRadius = radius - enemyConfig.thickness;
    enemy->addComponent<CollisionComponent>(collisionRadius);
    enemy->addComponent<ShapeComponent>(radius, enemyConfig.outlineColor, BLACK, enemyConfig.thickness);
    int startX = random.between(radius, game.width - radius);
    int startY = random.between(radius, game.height - radius);
    auto center = Vec2(startX, startY);
    double direction = random.getf(1.0f) * M_2_PI;
    const auto speed = random.betweenf(enemyConfig.speed.first, enemyConfig.speed.second);
    enemy->addComponent<TransformComponent>(center, speed, direction);
    Logger::info("Entity[%s] created at: [%d, %d] with radius: %d", name.c_str(), startX, startY, radius);
  }
}

void BallScene::movementSystem() {
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

void BallScene::collisionSystem() {
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
      player->getComponent<TransformComponent>().position = Vec2(game.width / 2, game.height / 2);

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
        auto& a = enemy->getComponent<TransformComponent>();
        auto& b = otherEnemy->getComponent<TransformComponent>();

        float dx = a.position.x - b.position.x;
        float dy = a.position.y - b.position.y;
        float distance = std::sqrt(dx * dx + dy * dy);

        if (distance == 0.0f) break;

        // Normalize direction vector
        float nx = dx / distance;
        float ny = dy / distance;

        // Relative velocity
        float vxRelative = a.velocity.x - b.velocity.x;
        float vyRelative = a.velocity.y - b.velocity.y;

        // Velocity along normal
        float dotProduct = vxRelative * nx + vyRelative * ny;

        if (dotProduct > 0) return;  // Already separating

        float e = 1.0f; // Coefficient of restitution (elastic collision)
        float impulse = (2 * dotProduct) / (BALL_MASS + BALL_MASS);

        // Swap velocities along normal direction
        a.velocity.x -= impulse * nx;
        a.velocity.y -= impulse * ny;
        b.velocity.x += impulse * nx;
        b.velocity.y += impulse * ny;

        // TODO: resolve collision overlapping (circles can attach or stick together)
      }
    }
  endloop:;
  }
}

void BallScene::lifecycleSystem() {
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

bool BallScene::checkScreenCollision(TransformComponent& transform, CollisionComponent& collision) const {
  Vec2& velocity = transform.velocity;
  Vec2& position = transform.position;
  float x = position.x;
  float y = position.y;

  bool collide = false;

  Uint32 radius = collision.radius;
  float right = game.width - radius;
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
  Uint32 bottom = game.height - radius;
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

void BallScene::renderSystem() {
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
        shape.circle.draw(game.renderer, transform.position);
      }
    }
  }
}

void BallScene::updatePlayerPosition() {
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
