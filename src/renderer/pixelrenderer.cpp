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

void PixelRenderer::drawLine(const Vec2 &from, const Vec2 &to) {
    drawLine(from.x, from.y, to.x, to.y);
}

void PixelRenderer::drawRect(const SDL_Rect *pRect) {
    SDL_RenderDrawRect(pSDLRenderer, pRect);
}

void PixelRenderer::drawCircle(const Vec2 &center, int radius) {
    int centerX = (int) center.x;
    int centerY = (int) center.y;
    for (int y = -radius; y <= radius; ++y) {
        for (int x = -radius; x <= radius; ++x) {
            if (x * x + y * y <= radius * radius) {
                drawPoint(centerX + x, centerY + y);
            }
        }
    }
}

void PixelRenderer::renderText(const std::string &text, const Uint32 x, const Uint32 y) {
    SDL_Color color = {255, 255, 255}; // White text color
    SDL_Surface *surface = TTF_RenderText_Solid(this->font, text.c_str(), color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(pSDLRenderer, surface);
    SDL_Rect textRect = {(int) x, (int) y, surface->w, surface->h};

    SDL_RenderCopy(pSDLRenderer, texture, nullptr, &textRect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void PixelRenderer::renderTexture(SDL_Texture *texture, const Vec2 &size, const Vec2 &dest) {
    SDL_Rect rect = {(int) dest.x, (int) dest.y, (int) size.x, (int) size.y};
    SDL_RenderCopy(pSDLRenderer, texture, nullptr, &rect);
}

void PixelRenderer::drawPoint(const Vec2 &point) {
    drawPoint(int(point.x), int(point.y));
}

void PixelRenderer::drawPoint(const int x, const int y) {
    SDL_RenderDrawPoint(pSDLRenderer, x, y);
}

