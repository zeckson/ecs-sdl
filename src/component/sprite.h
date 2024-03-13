//
// Created by Evgenii Shchepotev on 27.02.2024.
//

#ifndef ECS_SDL_SPRITE_H
#define ECS_SDL_SPRITE_H

#include <SDL2/SDL.h>

struct Sprite {
    const SDL_Texture* texture;
    const Uint16 width;
    const Uint16 height;
};

#endif //ECS_SDL_SPRITE_H
