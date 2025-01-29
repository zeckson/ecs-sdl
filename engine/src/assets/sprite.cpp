//
// Created by Evgenii Shchepotev on 06.04.2024.
//

#include "sprite.h"

Sprite::Sprite(const std::string& name, SDL_Texture* sdlTexture, int width, int height)
    : name(name), sdlTexture(sdlTexture), width(width), height(height) {}

Sprite::Sprite(const std::string& name, SDL_Texture* sdlTexture, SDL_Surface* surface)
    : Sprite(name, sdlTexture, surface->w, surface->h) {}

Sprite::~Sprite() {}

const Vec2 Sprite::getBBox() const {
  return {width, height};
}

void Sprite::rotate(const double angleDeg) { angle = angleDeg; }

void Sprite::render(SDL_Renderer* renderer, const Vec2& dest) const {
  SDL_Rect rect = {int(dest.x), (int)dest.y, width, height};
  const SDL_Point center = SDL_Point{int(rect.w / 2), int(rect.h / 2)};
  SDL_RenderCopyEx(renderer, sdlTexture, nullptr,  //
                   &rect,                          //
                   angle, &center, SDL_FLIP_NONE);

  auto size = getBBox();
  SDL_Rect bbox = {int(dest.x), int(dest.y), (int)size.x, (int)size.y};

  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
  SDL_RenderDrawRect(renderer, &bbox);
}
