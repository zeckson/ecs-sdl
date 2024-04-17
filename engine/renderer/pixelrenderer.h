//
// Created by Evgenii Shchepotev on 28.01.2024.
//

#ifndef RAYCASTING_PIXELRENDERER_H
#define RAYCASTING_PIXELRENDERER_H

#include <memory>
#include <string>

#include "../assets/assetsmanager.h"
#include "../geometry/vec2.h"
#include "SDL.h"
#include "SDL_ttf.h"
#include "pixel.h"

class PixelRenderer {
 public:
  const Uint16 width, height;

  explicit PixelRenderer(SDL_Renderer* renderer, const AssetsManager& manager, const Uint16 width, const Uint16 height)
      : width(width), height(height), manager(manager), pSDLRenderer(renderer) {}

  ~PixelRenderer() {}

  PixelRenderer* setColor(const Pixel& pixel);

  PixelRenderer* clear();

  PixelRenderer* present();

  void drawLine(Uint32 startX, Uint32 startY, Uint32 endX, Uint32 endY);

  void drawLine(const Vec2& from, const Vec2& to);

  void drawPoint(const Vec2& point);

  void drawPoint(const int x, const int y);

  void drawRect(const SDL_Rect* pRect);

  void drawCircle(const Vec2& center, int radius);

  void renderText(const std::string& text, const Uint32 x, const Uint32 y);

  void renderTexture(SDL_Texture* texture, const Vec2& size, const Vec2& dest);

  SDL_Renderer* renderer() { return pSDLRenderer; }

 private:
  const AssetsManager& manager;
  SDL_Renderer* pSDLRenderer;
};

#endif  // RAYCASTING_PIXELRENDERER_H
