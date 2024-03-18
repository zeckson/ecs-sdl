//
// Created by Evgenii Shchepotev on 14.03.2024.
//

#include "app.h"
#include "logger.h"

App::App(const char *title, const Uint16 width, const Uint16 height) {
    SDL_LogSetAllPriority(SDL_LOG_PRIORITY_WARN);
    SDL_LogSetPriority(ApplicationLog::GAME_ENGINE, SDL_LOG_PRIORITY_INFO);

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not be initialized: %s", SDL_GetError());
    } else {
        printf("SDL video system is ready to go\n");
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

    SDL_Renderer *sdlRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);


    if (!sdlRenderer) {
        printf("Failed to create renderer: %s\n", SDL_GetError());
        exit(1);
    }

    // Loading textures
    // Init img support
    if (!(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))) {
        printf("SDL_image initialization failed: %s\n", IMG_GetError());
        exit(1);
    }

    /* Initialize the TTF library */
    if (TTF_Init() < 0) {
        printf("Couldn't initialize TTF: %s\n", SDL_GetError());
        exit(1);
    }

    font = TTF_OpenFont(FONT_PATH, DEFAULT_FONT_SIZE);
    if (font == nullptr) {
        printf("Couldn't load %d pt font from %s: %s\n",
               DEFAULT_FONT_SIZE, FONT_PATH, SDL_GetError());
        // Handle font loading error
        exit(1);
    }

    pSDLRenderer = sdlRenderer;
}

void App::destroy() {
    TTF_CloseFont(font);
    TTF_Quit();

    SDL_DestroyRenderer(pSDLRenderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}