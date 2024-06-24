//
// Created by Evgenii Shchepotev on 14.03.2024.
//

#ifndef ECS_SDL_COLLISIONCOMPONENT_H
#define ECS_SDL_COLLISIONCOMPONENT_H

#include <SDL.h>

#include "component.h"

#define COLLISION_COMPONENT_NAME "collision"

class CollisionComponent : public Component {
 public:
  CollisionComponent(const int radius) : Component(COLLISION_COMPONENT_NAME), radius(radius) {}

  const int radius;
};

#endif  // ECS_SDL_COLLISIONCOMPONENT_H
