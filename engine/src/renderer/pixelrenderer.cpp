//
// Created by Evgenii Shchepotev on 28.01.2024.
//
#include "pixelrenderer.h"

#include <SDL.h>

#include "textrenderer.h"

PixelRenderer* PixelRenderer::setColor(const Pixel& pixel) {
  SDL_SetRenderDrawColor(pSDLRenderer, pixel.r(), pixel.g(), pixel.b(), pixel.a());
  return this;
}

PixelRenderer* PixelRenderer::clear() {
  SDL_RenderClear(pSDLRenderer);
  return this;
}

PixelRenderer* PixelRenderer::present() {
  SDL_RenderPresent(pSDLRenderer);
  return this;
}

void PixelRenderer::drawLine(Uint32 startX, Uint32 startY, Uint32 endX, Uint32 endY) {
  SDL_RenderDrawLine(pSDLRenderer, startX, startY, endX, endY);
}

void PixelRenderer::drawLine(const Vec2& from, const Vec2& to) { drawLine(from.x, from.y, to.x, to.y); }

void PixelRenderer::drawRect(const SDL_Rect* pRect, bool fill) {
  if (fill) {
    SDL_RenderFillRect(pSDLRenderer, pRect);
  } else {
    SDL_RenderDrawRect(pSDLRenderer, pRect);
  }
}

void PixelRenderer::drawCircle(const Vec2& center, int radius) {
  int centerX = (int)center.x;
  int centerY = (int)center.y;
  for (int y = -radius; y <= radius; ++y) {
    for (int x = -radius; x <= radius; ++x) {
      if (x * x + y * y <= radius * radius) {
        drawPoint(centerX + x, centerY + y);
      }
    }
  }
}

void PixelRenderer::renderText(const std::string& text, const Uint32 x, const Uint32 y) {
  renderText(text, x, y, WHITE);
}

void PixelRenderer::renderText(const std::string& text, const Uint32 x, const Uint32 y, const Pixel& color) {
  auto builder = TextRenderer::Builder(manager.getFont("glitchgoblin"));
  builder.justify(TextRenderer::Left).ofSize({0, 0}).withText(text).withColor(color);
  render(builder.build(), {(int)x, (int)y});
}

void PixelRenderer::renderTexture(SDL_Texture* texture, const Vec2& size, const Vec2& dest) {
  SDL_Rect rect = {int(dest.x), (int)dest.y, int(size.y), int(size.x)};
  const SDL_Point center = SDL_Point{int(size.x / 2), int(size.y / 2)};
  SDL_RenderCopyEx(renderer(), texture, nullptr,  //
                   &rect,                         //
                   90, &center, SDL_FLIP_NONE);
}

void PixelRenderer::drawPoint(const Vec2& point) { drawPoint(int(point.x), int(point.y)); }

void PixelRenderer::drawPoint(const int x, const int y) { SDL_RenderDrawPoint(pSDLRenderer, x, y); }

void PixelRenderer::renderSprite(const std::shared_ptr<Sprite>& sprite, const Vec2& dest) {
  render(*sprite, dest);
}

void PixelRenderer::render(const Renderable& renderable, const Vec2& dest) const {
  renderable.render(pSDLRenderer, dest);
}
