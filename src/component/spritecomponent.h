//
// Created by Evgenii Shchepotev on 27.02.2024.
//

#ifndef ECS_SDL_SPRITECOMPONENT_H
#define ECS_SDL_SPRITECOMPONENT_H

#include <SDL2/SDL.h>
#include "component.h"

#define SPRITE_COMPONENT_NAME "sprite"

class SpriteComponent: public Component {

public:
    SpriteComponent(SDL_Texture *texture, const Uint16 width, const Uint16 height)
            : Component(SPRITE_COMPONENT_NAME), texture(texture), size({width, height}) {}

    SDL_Texture* texture;
    const Vec2<Uint32> size;
};

#endif //ECS_SDL_SPRITECOMPONENT_H
