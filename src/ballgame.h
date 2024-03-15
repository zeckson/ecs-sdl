//
// Created by Evgenii Shchepotev on 14.03.2024.
//

#ifndef ECS_SDL_BALLGAME_H
#define ECS_SDL_BALLGAME_H

#include "base/game.h"
#include "randomizer.h"


#define ENTITY_SPEED 400

class BallGame: public Game {
public:
    explicit BallGame(const char *title, Uint16 width, Uint16 height): Game(title, width, height) {}

protected:
    bool onGameCreate() override;

    bool onGameUpdate(float elapsedTime) override;

    void onKeyDown(const SDL_Keysym &keysym) override;

private:

    void spawnEnemySystem();

    void movementSystem(float elapsedTime);

    void collisionSystem();

    void renderSystem();

    void userInputSystem(const SDL_Keysym &keysym);

    std::shared_ptr<Entity> player;
    EntityManager manager;
    Randomizer random;
};


#endif //ECS_SDL_BALLGAME_H
