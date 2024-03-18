//
// Created by Evgenii Shchepotev on 15.03.2024.
//

#ifndef ECS_SDL_CIRCLE_H
#define ECS_SDL_CIRCLE_H


#include "../renderer/pixel.h"
#include "../renderer/pixelrenderer.h"

class Circle {
    int radius;
    Pixel outlineColor;
    Pixel fillColor;
    int thickness;

public:
    explicit Circle(int radius, const Pixel &outlineColor, const Pixel &fillColor, int thickness);

    void draw(const std::shared_ptr<PixelRenderer> &renderer, const Vec2 &position) const;
    void setOutlineColor(const Pixel &color);
    void setFillColor(const Pixel &color);

};


#endif //ECS_SDL_CIRCLE_H
