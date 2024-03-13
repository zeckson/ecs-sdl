//
// Created by Evgenii Shchepotev on 28.01.2024.
//

#ifndef RAYCASTING_PIXELRENDERER_H
#define RAYCASTING_PIXELRENDERER_H

#include <memory>
#include "SDL2/SDL.h"

#include "pixel.h"
#include "../entity/vec2.h"

class PixelRenderer {
public:
    const Uint16 width, height;

    explicit PixelRenderer(SDL_Renderer *renderer, const Uint16 width, const Uint16 height)
            : width(width), height(height),
            pSDLRenderer(renderer) {

    }

    ~PixelRenderer() {
    }

    PixelRenderer *setColor(const Pixel &pixel);
    PixelRenderer *clear();
    PixelRenderer *present();

    void drawLine(Uint32 startX, Uint32 startY, Uint32 endX, Uint32 endY);
    void drawLine(const Vec2<Uint32> &from, const Vec2<Uint32> &to);

    void drawRect(const SDL_Rect *pRect);

    void drawCircle(int centerX, int centerY, int radius);

private:
    SDL_Renderer* pSDLRenderer;
};


#endif //RAYCASTING_PIXELRENDERER_H
