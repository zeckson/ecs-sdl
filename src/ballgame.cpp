//
// Created by Evgenii Shchepotev on 14.03.2024.
//

#include <memory>
#include <cmath>

#include "ballgame.h"
#include "component/transformcomponent.h"
#include "component/shapecomponent.h"

bool BallGame::onGameCreate() {
    player = manager.createEntity("player");
    const auto radius = 60;
    player->collision = std::make_shared<CollisionComponent>(radius);
    player->shape = std::make_shared<ShapeComponent>(radius, GREEN, BLUE, 2);
    auto center = Vec2(float(width) / 2, float(height) / 2);
    player->transform = std::make_shared<TransformComponent>(center, 0, 0);
    player->input = std::make_shared<InputComponent>();
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
        enemy->transform = std::make_shared<TransformComponent>(center, ENEMY_SPEED, M_PI_4);
        logInfo("Entity[%s] created at: [%d, %d] with radius: %d", name, startX, startY, radius);
        manager.addEntity(enemy);
    }
}

bool BallGame::onGameUpdate(float elapsedTime) {
    manager.update();

    spawnEnemySystem();
    movementSystem(elapsedTime);
    collisionSystem();
    renderSystem();
    updatePlayerPosition();

    return true;
}

void BallGame::movementSystem(float elapsedTime) {
    for (const auto &entity: manager.getAllEntities()) {
        auto &component = entity->transform;
        if (component) {
            component->position.x += std::round(component->velocity.x);
            component->position.y += std::round(component->velocity.y);
        }
        if (entity == player) {
            updatePlayerPosition();
        }
    }

}

void BallGame::collisionSystem() {
    for (const auto &entity: manager.getAllEntities()) {
        auto &transform = entity->transform;
        auto &collision = entity->collision;
        if (transform && collision) {
            borderCollision(transform, collision);
        }
    }
}

void BallGame::borderCollision(const std::shared_ptr<TransformComponent> &transform,
                               const std::shared_ptr<CollisionComponent> &collision) const {
    Vec2 &velocity = transform->velocity;
    Vec2 &position = transform->position;
    Uint32 x = position.x;
    Uint32 y = position.y;
    Uint32 radius = collision->radius;
    Uint32 right = width - radius;
    Uint32 left = 0 + radius;
    if (x >= right) {
        velocity.x *= -1.0;
        position.x = right;
    }
    if (x <= left) {
        velocity.x *= -1.0;
        position.x = left;
    }
    Uint32 bottom = height - radius;
    Uint32 top = 0 + radius;
    if (y >= bottom) {
        velocity.y *= -1.0;
        position.y = bottom;
    }
    if (y <= top) {
        velocity.y *= -1.0;
        position.y = top;
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

void BallGame::updatePlayerPosition() {
    const auto &input = player->input;
    if (input) {
        const auto &transform = player->transform;
        if (transform) {
            float yAxisMove = 0;
            if (input->isset(Direction::UP)) yAxisMove -= 1;
            if (input->isset(Direction::DOWN)) yAxisMove += 1;

            float xAxisMove = 0;
            if (input->isset(Direction::LEFT)) xAxisMove -= 1;
            if (input->isset(Direction::RIGHT)) xAxisMove += 1;

            // TODO: fix diagonal movement speed (should be sqrt(2))
            transform->position.x += xAxisMove * PLAYER_SPEED;
            transform->position.y += yAxisMove * PLAYER_SPEED;
        }
    }
}

void BallGame::onKeyEvent(const SDL_Event &event) {
    const auto key = event.key.keysym;

    logInfo("Keyevent[%u] code: %u", event.type, key.scancode);

    for (const auto &entity: manager.getAllEntities()) {
        const auto input = entity->input;
        if (input) {
            if (event.type == SDL_KEYDOWN) {
                switch (key.scancode) {
                    case SDL_SCANCODE_UP:
                        input->set(Direction::UP);
                        break;
                    case SDL_SCANCODE_DOWN:
                        input->set(Direction::DOWN);
                        break;
                    case SDL_SCANCODE_LEFT:
                        input->set(Direction::LEFT);
                        break;
                    case SDL_SCANCODE_RIGHT:
                        input->set(Direction::RIGHT);
                        break;
                    default:
                        // do nothing
                        break;
                }
            }
            if (event.type == SDL_KEYUP) {
                switch (key.scancode) {
                    case SDL_SCANCODE_UP:
                        input->unset(Direction::UP);
                        break;
                    case SDL_SCANCODE_DOWN:
                        input->unset(Direction::DOWN);
                        break;
                    case SDL_SCANCODE_LEFT:
                        input->unset(Direction::LEFT);
                        break;
                    case SDL_SCANCODE_RIGHT:
                        input->unset(Direction::RIGHT);
                        break;
                    default:
                        // do nothing
                        break;
                }
            }
        }
    }

}

void BallGame::onMouseEvent(const SDL_Event &event) {

}
