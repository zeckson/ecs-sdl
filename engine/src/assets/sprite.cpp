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
  double radians = angle * M_PI / 180.0;

  double cosTheta = cos(radians);
  double sinTheta = sin(radians);

  SDL_Point center = {width / 2, height / 2};
  SDL_Point position = {center.x, center.y};

  SDL_Point rotated = {center.x + (int)(position.x * cosTheta - position.y * sinTheta),
                       center.y + (int)(position.x * sinTheta + position.y * cosTheta)};

  int minX = SDL_min(width - rotated.x, width);
  int minY = SDL_min(height - rotated.y, height);

  int maxX = SDL_max(rotated.x + width, width);
  int maxY = SDL_max(rotated.y + height, height);

  return {maxX - minX, maxY - minY};
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
