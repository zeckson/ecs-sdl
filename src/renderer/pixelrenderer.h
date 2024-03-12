//
// Created by Evgenii Shchepotev on 28.01.2024.
//

#ifndef RAYCASTING_PIXELRENDERER_H
#define RAYCASTING_PIXELRENDERER_H

#include <memory>
#include "SDL2/SDL.h"

#include "pixel.h"

class PixelRenderer {
public:
    const Uint16 width, height;

    explicit PixelRenderer(SDL_Window *window, const Uint16 width, const Uint16 height)
            : width(width), height(height),
            pSDLRenderer(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE)) {

    }

    ~PixelRenderer() {
        destroy();
    }

    PixelRenderer *setColor(const Pixel &pixel);
    PixelRenderer *clear();
    PixelRenderer *present();

    void destroy();

    void drawLine(int startX, int startY, int endX, int endY);

    void drawRect(const SDL_Rect *pRect);

    void drawCircle(int centerX, int centerY, int radius);

private:
    SDL_Renderer* pSDLRenderer;
};


#endif //RAYCASTING_PIXELRENDERER_H
