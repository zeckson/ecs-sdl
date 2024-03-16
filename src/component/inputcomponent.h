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
        left = false;
        right = false;
        up = false;
        down = false;
    }

    bool left = false;
    bool right = false;
    bool up = false;
    bool down = false;
};


#endif //ECS_SDL_INPUTCOMPONENT_H
