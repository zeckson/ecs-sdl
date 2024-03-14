//
// Created by Evgenii Shchepotev on 14.03.2024.
//

#include "ballgame.h"
#include "component/transformcomponent.h"
#include <memory>

bool BallGame::onGameCreate() {
    auto player = manager.createEntity("player");
    player->sprite = std::make_shared<SpriteComponent>(nullptr, 60, 60);
    auto center = Vec2<Uint32>((Uint32) width / 2, (Uint32) height / 2);
    auto toRight = Vec2<float>{1.0, 1.0};
    player->transform = std::make_shared<TransformComponent>(center, toRight, 0);
    manager.addEntity(player);
    return true;
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

void BallGame::spawnEnemySystem() {
    // TODO: spawn enemy every 1000 frames
}

void BallGame::movementSystem(float elapsedTime) {
    for (const auto &entity: manager.getAllEntities()) {
        auto &component = entity->transform;
        float speed = ENTITY_SPEED * elapsedTime;
        if (component) {
            component->position.x += (component->velocity.x * speed);
            component->position.y += (component->velocity.y * speed);
        }
    }

}

void BallGame::collisionSystem() {
    for (const auto &entity: manager.getAllEntities()) {
        auto &component = entity->transform;
        if (component) {
            Uint32 x = component->position.x;
            Uint32 radius = entity->sprite->size.x;
            if (x >= width - radius) {
                component->velocity.x = -1.0;
            }
            if (x <= 0 + radius) {
                component->velocity.x = 1.0;
            }
            Uint32 y = component->position.y;
            if (y >= height - radius) {
                component->velocity.y = -1.0;
            }
            if (y <= 0 + radius) {
                component->velocity.y = 1.0;
            }
        }
    }
}

void BallGame::renderSystem() {
    for (const auto &entity: manager.getAllEntities()) {
        auto &component = entity->sprite;
        if (component) {
            if (component->texture) {
                renderer->renderTexture(component->texture, component->size, entity->transform->position);
            } else {
                renderer->setColor(RED);
                renderer->drawCircle(entity->transform->position, (int) component->size.x);
            }
        }
    }
}

void BallGame::userInputSystem(const SDL_Keysym &keysym) {

}
