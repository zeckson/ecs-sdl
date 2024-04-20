//
// Created by Evgenii Shchepotev on 06.04.2024.
//

#ifndef ECS_SPRITE_H
#define ECS_SPRITE_H

#include <SDL.h>

#include <string>

#include "geometry/vec2.h"

class Sprite {
  const std::string& name;
  const SDL_Texture* sdlTexture;

 public:
  const int height;
  const int width;

  double angle = 0;


  explicit Sprite(const std::string& name, SDL_Texture* sdlTexture, SDL_Surface* surface);

  // Delete copy constructor
  Sprite(const Sprite&) = delete;

  // Delete move constructor
  Sprite(Sprite&&) = delete;

  // Delete copy assignment operator
  Sprite& operator=(const Sprite&) = delete;

  // Delete move assignment operator
  Sprite& operator=(Sprite&&) = delete;

  virtual ~Sprite();

  Vec2&& getBBox() const;

  void rotate(double angleDeg);

  SDL_Texture* texture() { return const_cast<SDL_Texture*>(sdlTexture); }
};

#endif  // ECS_SPRITE_H
