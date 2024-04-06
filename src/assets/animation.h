//
// Created by Evgenii Shchepotev on 06.04.2024.
//

#ifndef ECS_ANIMATION_H
#define ECS_ANIMATION_H

#include "SDL2/SDL.h"


class Animation {
    const SDL_Texture* texturePointer;
public:
    explicit Animation(const SDL_Texture *texturePointer);

    virtual ~Animation();
};


#endif //ECS_ANIMATION_H
