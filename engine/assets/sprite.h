//
// Created by Evgenii Shchepotev on 06.04.2024.
//

#ifndef ECS_SPRITE_H
#define ECS_SPRITE_H

#include <SDL.h>

#include <string>

class Sprite {
  const std::string name;
  const SDL_Texture* sdlTexture;

 public:
  const int height;
  const int width;

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

  SDL_Texture* texture() { return const_cast<SDL_Texture*>(sdlTexture); }
};

#endif  // ECS_SPRITE_H
