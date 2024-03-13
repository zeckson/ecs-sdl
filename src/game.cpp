//
// Created by Evgenii Shchepotev on 28.01.2024.
//

#include <iostream>

#include "game.h"

Game::Game(const char *title, Uint16 width, Uint16 height) : width(width), height(height) {
    SDL_LogSetAllPriority(SDL_LOG_PRIORITY_WARN);

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not be initialized: " << SDL_GetError();
    } else {
        std::cout << "SDL video system is ready to go\n";
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    // Create an application window with the following settings:
    window = SDL_CreateWindow(
            title,        // window title
            SDL_WINDOWPOS_CENTERED, // initial x position
            SDL_WINDOWPOS_CENTERED, // initial y position
            width,                     // width, in pixels
            height,                     // height, in pixels
            SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL
    );

    // Check that the window was successfully created
    if (!window) {
        // In the case that the window could not be made...
        printf("Failed to open %d x %d window: %s\n", width, height, SDL_GetError());
        exit(1);
    }

    SDL_Renderer *sdlRenderer = SDL_CreateRenderer(window, -1,
                                                   SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);


    if (!sdlRenderer) {
        printf("Failed to create renderer: %s\n", SDL_GetError());
        exit(1);
    }

    pSDLRenderer = sdlRenderer;

    renderer = std::make_shared<PixelRenderer>(sdlRenderer, width, height);
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

        quit = update(frameTime);

        renderer->present();

        //timing for input and FPS counter
        frame++;
        oldTime = time;
        time = SDL_GetTicks();
        frameTime = (time - oldTime) / 1000.0; //frameTime is the time this frame has taken, in seconds
//        print(1.0 / frameTime); //FPS counter
//        redraw();
//        cls();
    }

    SDL_DestroyRenderer(pSDLRenderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
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
