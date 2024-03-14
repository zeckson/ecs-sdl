//
// Created by Evgenii Shchepotev on 14.03.2024.
//

#ifndef ECS_SDL_BALLGAME_H
#define ECS_SDL_BALLGAME_H

#include "game.h"


class BallGame: public Game {
public:
    explicit BallGame(const char *title, Uint16 width, Uint16 height): Game(title, width, height) {}

protected:
    bool onGameCreate() override;

    bool onGameUpdate(double elapsedTime) override;

    void onKeyDown(const SDL_Keysym &keysym) override;

};


#endif //ECS_SDL_BALLGAME_H
