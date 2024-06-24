//
// Created by Evgenii Shchepotev on 06.04.2024.
//

#ifndef ECS_ANIMATION_H
#define ECS_ANIMATION_H

#include "SDL.h"
#include "sprite.h"

class Animation {
  const Sprite& origin;

 public:
  explicit Animation(const Sprite& originalSprite);;

  virtual ~Animation();
};

#endif  // ECS_ANIMATION_H
