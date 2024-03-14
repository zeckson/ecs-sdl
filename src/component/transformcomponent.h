//
// Created by Evgenii Shchepotev on 14.03.2024.
//

#ifndef ECS_SDL_TRANSFORMCOMPONENT_H
#define ECS_SDL_TRANSFORMCOMPONENT_H

#include "SDL2/SDL.h"

#include "../entity/vec2.h"
#include "component.h"

#define TRANSFORM_COMPONENT_NAME "transform"

class TransformComponent : public Component {
public:
    TransformComponent(const Vec2<Uint32> &position, const Vec2<float> &speed, float angle) :
            Component(TRANSFORM_COMPONENT_NAME), position(position), velocity(speed), angle(angle) {}

    Vec2<Uint32> position;
    Vec2<float> velocity;
    float angle; // radians
};


#endif //ECS_SDL_TRANSFORMCOMPONENT_H
