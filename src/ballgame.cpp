//
// Created by Evgenii Shchepotev on 14.03.2024.
//

#include <memory>

#include "ballgame.h"
#include "component/transformcomponent.h"
#include "component/shapecomponent.h"

bool BallGame::onGameCreate() {
    std::srand(time(nullptr));

    player = manager.createEntity("player");
    const auto radius = 60;
    player->collision = std::make_shared<CollisionComponent>(radius);
    player->shape = std::make_shared<ShapeComponent>(radius, GREEN, BLUE, 2);
    auto center = Vec2(float(width) / 2, float(height) / 2);
    auto toRight = Vec2(1.0, 1.0);
    player->transform = std::make_shared<TransformComponent>(center, toRight, 0);
    manager.addEntity(player);
    return true;
}

void BallGame::spawnEnemySystem() {
    if (frameRate.totalFrame % 1000 == 0 && manager.getAllEntities().size() < 10) {
        const char *name = "enemy";
        auto enemy = manager.createEntity(name);
        int radius = random.between(10, 40);
        enemy->collision = std::make_shared<CollisionComponent>(radius);
        enemy->shape = std::make_shared<ShapeComponent>(radius, BLUE, RED);
        int startX = random.between(radius, width - radius);
        int startY = random.between(radius, height - radius);
        auto center = Vec2(startX, startY);
        auto velocity = Vec2(-4, 4);
        enemy->transform = std::make_shared<TransformComponent>(center, velocity, 0);
        logInfo("Entity[%s] created at: [%d, %d] with radius: %d", name, startX, startY, radius);
//        logInfo("Entity created: %u", 120);
        manager.addEntity(enemy);
    }
}

bool BallGame::onGameUpdate(float elapsedTime) {
    manager.update();

    spawnEnemySystem();
    movementSystem(elapsedTime);
    collisionSystem();
    renderSystem();

    return true;
}

void BallGame::onKeyDown(const SDL_Keysym &keysym) {
    userInputSystem(keysym);
}

void BallGame::movementSystem(float elapsedTime) {
    for (const auto &entity: manager.getAllEntities()) {
        auto &component = entity->transform;
        float speed = ENTITY_SPEED * elapsedTime;
        if (component) {
            component->position.x += std::round(component->velocity.x * speed);
            component->position.y += std::round(component->velocity.y * speed);
        }
    }

}

void BallGame::collisionSystem() {
    for (const auto &entity: manager.getAllEntities()) {
        auto &transform = entity->transform;
        auto &collision = entity->collision;
        if (transform && collision) {
            Uint32 x = transform->position.x;
            Uint32 radius = collision->radius;
            if (x >= width - radius) {
                transform->velocity.x = -1.0;
            }
            if (x <= 0 + radius) {
                transform->velocity.x = 1.0;
            }
            Uint32 y = transform->position.y;
            if (y >= height - radius) {
                transform->velocity.y = -1.0;
            }
            if (y <= 0 + radius) {
                transform->velocity.y = 1.0;
            }
        }
    }
}

void BallGame::renderSystem() {
    for (const auto &entity: manager.getAllEntities()) {
        const auto &component = entity->shape;
        const auto transform = entity->transform;
        if (component && transform) {
            component->circle.draw(renderer, transform->position);
        }
    }
}

void BallGame::userInputSystem(const SDL_Keysym &keysym) {

}
