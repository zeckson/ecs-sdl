//
// Created by Evgenii Shchepotev on 27.02.2024.
//

#ifndef ECS_SDL_SHAPECOMPONENT_H
#define ECS_SDL_SHAPECOMPONENT_H

#include <SDL2/SDL.h>

#include "component.h"
#include "../geometry/vec2.h"
#include "../geometry/circle.h"

#define SHAPE_COMPONENT_NAME "shape"

class ShapeComponent: public Component {

public:
    const Circle circle;

    ShapeComponent(int radius, const Pixel &outline, const Pixel &fill, const int thickness = 1)
            : Component(SHAPE_COMPONENT_NAME), circle(Circle(radius, outline, fill, thickness)) {}
};

#endif //ECS_SDL_SHAPECOMPONENT_H
