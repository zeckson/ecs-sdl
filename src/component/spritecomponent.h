//
// Created by Evgenii Shchepotev on 27.02.2024.
//

#ifndef ECS_SDL_SPRITECOMPONENT_H
#define ECS_SDL_SPRITECOMPONENT_H

#include <SDL.h>

#include "../geometry/vec2.h"
#include "component.h"

#define SPRITE_COMPONENT_NAME "sprite"

class SpriteComponent : public Component {
 public:
  SpriteComponent(SDL_Texture* texture, const Uint16 width, const Uint16 height)
      : Component(SPRITE_COMPONENT_NAME), texture(texture), size({float(width), float(height)}) {}

  SDL_Texture* texture;
  const Vec2 size;
};

#endif  // ECS_SDL_SPRITECOMPONENT_H
