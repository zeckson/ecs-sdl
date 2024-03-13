//
// Created by Evgenii Shchepotev on 28.01.2024.
//
#include "SDL2/SDL.h"

#include "pixelrenderer.h"

PixelRenderer *PixelRenderer::setColor(const Pixel &pixel) {
    SDL_SetRenderDrawColor(pSDLRenderer, pixel.r(), pixel.g(), pixel.b(), pixel.a());
    return this;
}

PixelRenderer *PixelRenderer::clear() {
    SDL_RenderClear(pSDLRenderer);
    return this;
}

PixelRenderer *PixelRenderer::present() {
    SDL_RenderPresent(pSDLRenderer);
    return this;
}

void PixelRenderer::drawLine(Uint32 startX, Uint32 startY, Uint32 endX, Uint32 endY) {
    SDL_RenderDrawLine(pSDLRenderer, startX, startY, endX, endY);
}

void PixelRenderer::drawLine(const Vec2<Uint32> &from, const Vec2<Uint32> &to) {
    drawLine(from.x, from.y, to.x, to.y);
}

void PixelRenderer::drawRect(const SDL_Rect *pRect) {
    SDL_RenderDrawRect(pSDLRenderer, pRect);
}

void PixelRenderer::drawCircle(int centerX, int centerY, int radius) {
    for (int y = -radius; y <= radius; ++y) {
        for (int x = -radius; x <= radius; ++x) {
            if (x * x + y * y <= radius * radius) {
                SDL_RenderDrawPoint(pSDLRenderer, centerX + x, centerY + y);
            }
        }
    }
}

