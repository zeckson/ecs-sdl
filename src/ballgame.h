//
// Created by Evgenii Shchepotev on 14.03.2024.
//

#ifndef ECS_SDL_BALLGAME_H
#define ECS_SDL_BALLGAME_H

#include "base/game.h"
#include "randomizer.h"

#define PLAYER_SPEED 1.0
#define ENEMY_SPEED 2.0
#define BULLET_SPEED 4.0

#define ENTITY_BULLET_TAG "bullet"
#define ENTITY_ENEMY_TAG "enemy"
#define ENTITY_PLAYER_TAG "player"

#define BULLET_LIFECYCLE 100

class BallGame : public Game {
public:
    explicit BallGame(const char *title, Uint16 width, Uint16 height) : Game(title, width, height) {}

protected:
    bool onGameCreate() override;

    bool onGameUpdate(float elapsedTime) override;

    void onKeyEvent(const SDL_Event &event) override;

    void onMouseEvent(const SDL_Event &event) override;

private:

    void spawnEnemySystem();

    void movementSystem();

    void collisionSystem();

    void renderSystem();

    void lifecycleSystem();

    void updatePlayerPosition();

    bool checkScreenCollision(const std::shared_ptr<TransformComponent> &transform,
                              const std::shared_ptr<CollisionComponent> &collision) const;

    std::shared_ptr<Entity> player;
    EntityManager manager;
    Randomizer random;

    void spawnBullet(const Vec2 &target);
};


#endif //ECS_SDL_BALLGAME_H
