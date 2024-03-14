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
    auto toRight = Vec2<float>{400.0, 0.0};
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
        if (component) {
            component->position.x += (Uint32) (component->velocity.x * elapsedTime);
            component->position.y += (Uint32) (component->velocity.y * elapsedTime);
        }
    }

}

void BallGame::collisionSystem() {
    // TODO
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
//    renderer->drawCircle(width / 2, height / 2, std::min(width, height) / 4);
}

void BallGame::userInputSystem(const SDL_Keysym &keysym) {

}
