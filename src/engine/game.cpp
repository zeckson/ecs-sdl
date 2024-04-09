//
// Created by Evgenii Shchepotev on 28.01.2024.
//

#include <iostream>

#include "game.h"
#include "../resource/logger.h"

Game::Game(const char *title, const Config &config) :
        width(config.window.width), height(config.window.height), config(config), app(App(title, config)) {
    renderer = std::make_unique<PixelRenderer>(app.pSDLRenderer, app.assetsManager, width, height);
}

void Game::start() {

    running = onGameCreate();

    while (running) {
        frameRate.frameStart();

        running = input();

        renderer->setColor(BLACK);
        renderer->clear();

        onGameUpdate();


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
            return false;
        }

        const auto &scancode = e.key.keysym.scancode;
        switch (e.type) {
            case SDL_KEYDOWN:
                // TODO: Show menu on escape
                if (scancode == SDL_SCANCODE_ESCAPE) {
                    // Just exit
                    return false;
                }
            case SDL_KEYUP:
                Logger::debug("Keyevent[%s] code: %u", e.type == SDL_KEYDOWN ? "keydown" : "keyup", scancode);
                onKeyEvent(e);
                break;

            case SDL_MOUSEMOTION:
            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
                onMouseEvent(e);
                break;
        }
    }

    return true;
}
