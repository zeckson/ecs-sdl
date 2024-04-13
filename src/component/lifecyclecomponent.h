//
// Created by Evgenii Shchepotev on 14.03.2024.
//

#ifndef ECS_SDL_LIFECYCLECOMPONENT_H
#define ECS_SDL_LIFECYCLECOMPONENT_H

#include <SDL.h>

#include "component.h"

#define LIFECYCLE_COMPONENT_NAME "lifecycle"

class LifecycleComponent : public Component {
public:
    LifecycleComponent(const int framesToLive) :
            Component(LIFECYCLE_COMPONENT_NAME), framesToLive(framesToLive) {}

    const int framesToLive;
    int framesLeft = framesToLive;
};


#endif //ECS_SDL_LIFECYCLECOMPONENT_H
