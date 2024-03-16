//
// Created by Evgenii Shchepotev on 28.01.2024.
//

#include <iostream>
#include <utility>

#include "game.h"

void FrameRate::limit() const {
    if (currentFrameTime <= DELAY_TIME) {
        SDL_Delay(DELAY_TIME - currentFrameTime);
    }
}

void FrameRate::render(const std::shared_ptr<PixelRenderer> &renderer) const {
    renderer->renderText("FPS: " + std::to_string(int(std::ceil(fps))), 5, 5);
    renderer->renderText("Delay Time: " + std::to_string(DELAY_TIME), 5, 30);
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


Game::Game(const char *title, Uint16 width, Uint16 height) :
        width(width), height(height), app(App(title, width, height)) {
    renderer = std::make_shared<PixelRenderer>(app.pSDLRenderer, app.font, width, height);
}

void Game::start() {

    onGameCreate();

    bool quit = false;
    while (!quit) {
        frameRate.frameStart();

        renderer->setColor(BLACK);
        renderer->clear();

        quit = input();

        onGameUpdate(frameRate.elapsedTime());

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

    bool quit;
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            quit = true;
        }

        if (e.type == SDL_KEYDOWN) {

            // Show menu on escape
            if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
                quit = true;
            }

            const SDL_Keysym &keysym = e.key.keysym;


            logInfo("Keydown code: %u", keysym.scancode);

            onKeyDown(keysym);
        }
    }
    return quit;
}

void Game::logInfo(const char* format, ...) {
    va_list args;
    va_start(args, format);
    SDL_LogMessageV(ApplicationLog::GAME_ENGINE, SDL_LOG_PRIORITY_INFO, format, args);
    va_end(args);
}