//
// Created by Evgenii Shchepotev on 14.03.2024.
//

#include "ballgame.h"

bool BallGame::onGameCreate() {
    return true;
}

bool BallGame::onGameUpdate(double elapsedTime) {
    renderer->setColor(RED);
    renderer->drawCircle(width / 2, height / 2, std::min(width, height) / 4);
    return true;
}

void BallGame::onKeyDown(const SDL_Keysym &keysym) {

}
