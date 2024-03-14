//
// Created by Evgenii Shchepotev on 28.01.2024.
//

#include <iostream>

#include "game.h"

Game::Game(const char *title, Uint16 width, Uint16 height) : width(width), height(height),
                                                             app(App(title, width, height)) {
    renderer = std::make_shared<PixelRenderer>(app.pSDLRenderer, app.font, width, height);
}

void Game::start() {
    Uint32 time = 0; //time of current frame
    Uint32 oldTime = 0; //time of previous frame

    double frameTime = 0;

    onGameCreate();

    bool quit = false;
    while (!quit) {

        renderer->setColor(BLACK);
        renderer->clear();

        renderer->renderText("FPS: " + std::to_string((int) std::floor(1.0 / frameTime)), 0, 0);

        quit = update(frameTime);

        renderer->present();

        //timing for input and FPS counter
        frame++;
        oldTime = time;
        time = SDL_GetTicks();
        frameTime = ((time - oldTime) / 1000.0); //frameTime is the time this frame has taken, in seconds
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


            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO,
                           "Keydown code: %u", keysym.scancode);

            onKeyDown(keysym);
        }
    }
    return quit;
}

bool Game::update(const float elapsedTime) {
    onGameUpdate(elapsedTime);
    return input();
}
