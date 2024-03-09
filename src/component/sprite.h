//
// Created by Evgenii Shchepotev on 27.02.2024.
//

#ifndef ECS_SDL_SPRITE_H
#define ECS_SDL_SPRITE_H

#include <SDL2/SDL.h>

struct Sprite {
    SDL_Texture* texture;
    int width;
    int height;
};

#endif //ECS_SDL_SPRITE_H
