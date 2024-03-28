//
// Created by Evgenii Shchepotev on 14.03.2024.
//

#ifndef ECS_SDL_APP_H
#define ECS_SDL_APP_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "../resource/config.h"

class Game;

class App {
    explicit App(const char *title, const Config &config);

    void destroy();

    SDL_Renderer *pSDLRenderer;
    TTF_Font *font;
    SDL_Window *window;

    friend class Game;
};


#endif //ECS_SDL_APP_H
