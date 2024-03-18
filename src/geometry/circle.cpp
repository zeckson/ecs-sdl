//
// Created by Evgenii Shchepotev on 15.03.2024.
//

#include "circle.h"

Circle::Circle(int radius, const Pixel &outlineColor, const Pixel &fillColor, int thickness)
        : radius(radius), outlineColor(outlineColor), fillColor(fillColor), thickness(thickness) {}

void Circle::draw(const std::shared_ptr<PixelRenderer> &renderer, const Vec2 &position) const {
    int centerX = (int) position.x;
    int centerY = (int) position.y;
    for (int y = -radius; y <= radius; ++y) {
        for (int x = -radius; x <= radius; ++x) {
            int border = (radius * radius);
            int location = x * x + y * y;
            if (location <= border) {
                if (border - location <= (thickness * 10) * (thickness * 10)) {
                    renderer->setColor(outlineColor);
                } else {
                    renderer->setColor(fillColor);
                }
                renderer->drawPoint(centerX + x, centerY + y);
            }
        }
    }
}

void Circle::setOutlineColor(const Pixel &color) {
    Circle::outlineColor = color;
}

void Circle::setFillColor(const Pixel &color) {
    Circle::fillColor = color;
}
