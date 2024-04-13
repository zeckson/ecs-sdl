//
// Created by Evgenii Shchepotev on 14.03.2024.
//

#ifndef ECS_SDL_TRANSFORMCOMPONENT_H
#define ECS_SDL_TRANSFORMCOMPONENT_H

#include <cmath>
#include <SDL.h>

#include "../geometry/vec2.h"
#include "component.h"

#define TRANSFORM_COMPONENT_NAME "transform"

class TransformComponent : public Component {
public:
    /*
     *  Speed in units / frame
     */
    TransformComponent(const Vec2 &position, const float speed, float angle) :
            TransformComponent(position, Util::toVelocity(speed, angle)) {}
    TransformComponent(const Vec2 &position, const Vec2 &velocity) :
            Component(TRANSFORM_COMPONENT_NAME), position(position), velocity(velocity) {}

    Vec2 position;
    Vec2 velocity;
};


#endif //ECS_SDL_TRANSFORMCOMPONENT_H
