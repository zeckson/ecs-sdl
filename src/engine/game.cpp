//
// Created by Evgenii Shchepotev on 28.01.2024.
//

#include <iostream>

#include "game.h"
#include "../resource/logger.h"

Game::Game(const char *title, const Config &config) :
        width(config.window.width), height(config.window.height), config(config), app(App(title, config)) {
    renderer = std::make_unique<PixelRenderer>(app.pSDLRenderer, app.font, width, height);
}

void Game::start() {

    onGameCreate();

    bool quit = false;
    while (!quit) {
        frameRate.frameStart();

        renderer->setColor(BLACK);
        renderer->clear();

        onGameUpdate(frameRate.elapsedTime());

        quit = input();

        frameRate.render(renderer);

        renderer->present();

        // timing for input and FPS counter
        frameRate.frameEnd();
        frameRate.limit();
    }

    app.destroy();
}

bool Game::input() {
    SDL_Event e;

    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            // Just exit
            return true;
        }

        switch (e.type) {
            case SDL_KEYDOWN:
                // TODO: Show menu on escape
                if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
                    // Just exit
                    return true;
                }
            case SDL_KEYUP:
                onKeyEvent(e);
                break;

            case SDL_MOUSEMOTION:
            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
                onMouseEvent(e);
                break;
        }
    }

    return false;
}
