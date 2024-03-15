//
// Created by Evgenii Shchepotev on 28.01.2024.
//

#ifndef RAYCASTING_PIXELRENDERER_H
#define RAYCASTING_PIXELRENDERER_H

#include <memory>
#include <string>
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

#include "pixel.h"
#include "../geometry/vec2.h"

class PixelRenderer {
public:
    const Uint16 width, height;

    explicit PixelRenderer(SDL_Renderer *renderer, TTF_Font *font, const Uint16 width, const Uint16 height)
            : width(width), height(height), font(font), pSDLRenderer(renderer) {
    }

    ~PixelRenderer() {
    }

    PixelRenderer *setColor(const Pixel &pixel);

    PixelRenderer *clear();

    PixelRenderer *present();

    void drawLine(Uint32 startX, Uint32 startY, Uint32 endX, Uint32 endY);

    void drawLine(const Vec2 &from, const Vec2 &to);

    void drawRect(const SDL_Rect *pRect);

    void drawCircle(const Vec2 &center, int radius);

    void renderText(const std::string &text, const Uint32 x, const Uint32 y);

    void renderTexture(SDL_Texture *texture, const Vec2 &size, const Vec2 &dest);

private:
    TTF_Font *font;
    SDL_Renderer *pSDLRenderer;
};


#endif //RAYCASTING_PIXELRENDERER_H
