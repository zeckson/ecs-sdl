//
// Created by Evgenii Shchepotev on 10.04.2024.
//

#include "spaceshipgame.h"

SpaceshipGame::SpaceshipGame(const char *title, const Config &config) : Game(title, config) {}

bool SpaceshipGame::onGameCreate() {
    return true;
}

void SpaceshipGame::onGameUpdate() {

    const std::unique_ptr<Texture> &texture = getAssetsManager().getTexture("spaceship");
    renderer->renderTexture(texture->texture(), {100, 100}, {100, 100});
}

void SpaceshipGame::onKeyEvent(const SDL_Event &event) {

}

void SpaceshipGame::onMouseEvent(const SDL_Event &event) {

}
