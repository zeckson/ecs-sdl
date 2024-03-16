//
// Created by Evgenii Shchepotev on 14.03.2024.
//

#ifndef ECS_SDL_APP_H
#define ECS_SDL_APP_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

#define FONT_PATH "gfx/glitchgoblin.ttf"
#define DEFAULT_FONT_SIZE 24

class Game;

enum ApplicationLog {
    GAME_ENGINE = SDL_LOG_CATEGORY_CUSTOM,
};

class App {
    explicit App(const char *title, Uint16 width, Uint16 height);

    void destroy();

    SDL_Renderer *pSDLRenderer;
    TTF_Font *font;
    SDL_Window *window;

    friend class Game;
};


#endif //ECS_SDL_APP_H
