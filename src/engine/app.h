//
// Created by Evgenii Shchepotev on 14.03.2024.
//

#ifndef ECS_SDL_APP_H
#define ECS_SDL_APP_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "../resource/config.h"
#include "../assets/assetsmanager.h"

class Game;

class App {
    explicit App(const char *title, const Config &config);

    SDL_Renderer *pSDLRenderer;
    SDL_Window *window;
    AssetsManager assetsManager = AssetsManager();


    SDL_Surface *loadSurface(const char *filename);

    SDL_Texture &loadTexture(const char *filename);

    void destroy();
    void loadFonts(const Config &config);
    friend class Game;
};


#endif //ECS_SDL_APP_H
