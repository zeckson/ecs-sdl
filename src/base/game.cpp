//
// Created by Evgenii Shchepotev on 28.01.2024.
//

#include <iostream>
#include <utility>

#include "game.h"
#include "logger.h"

void FrameRate::limit() const {
    if (currentFrameTime <= maxFrameTime) {
        SDL_Delay(Uint32(maxFrameTime) - currentFrameTime);
    }
}

void FrameRate::render(const std::unique_ptr<PixelRenderer> &renderer) const {
    renderer->renderText("FPS: " + std::to_string(int(std::ceil(fps))), 5, 5);
    renderer->renderText("Delay Time: " + std::to_string(maxFrameTime), 5, 30);
    renderer->renderText("Current Frame Time: " + std::to_string(currentFrameTime), 5, 55);
}

float FrameRate::elapsedTime() const {
    return float(currentFrameTime) / ONE_SECOND;
}

void FrameRate::frameStart() {
    frameStartTime = SDL_GetTicks();
}

void FrameRate::frameEnd() {
    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - startTime >= ONE_SECOND) {
        fps = ((double) frameCount / (currentTime - startTime)) * ONE_SECOND;

        // Reset frame rate counters
        startTime = frameStartTime;
        frameCount = 0;
    }

    currentFrameTime = currentTime - frameStartTime;
    totalFrame++;
    frameCount++;
}


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
