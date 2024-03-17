//
// Created by Evgenii Shchepotev on 14.03.2024.
//

#ifndef ECS_SDL_INPUTCOMPONENT_H
#define ECS_SDL_INPUTCOMPONENT_H

#include "SDL2/SDL.h"

#include "component.h"

#define INPUT_COMPONENT_NAME "input"

class InputComponent : public Component {
public:
    InputComponent() : Component(INPUT_COMPONENT_NAME) { reset(); }

    void reset() {
        xAxisMove = 0;
        yAxisMove = 0;

        fire = false;
    }

    int xAxisMove = 0;
    int yAxisMove = 0;
    bool fire = false;
};


#endif //ECS_SDL_INPUTCOMPONENT_H
