//
// Created by Evgenii Shchepotev on 15.03.2024.
//

#include "circle.h"

Circle::Circle(int radius, const Pixel &outlineColor, const Pixel &fillColor, int thickness)
        : radius(radius), outlineColor(outlineColor), fillColor(fillColor), thickness(thickness) {}

void Circle::draw(const std::unique_ptr<PixelRenderer> &renderer, const Vec2 &position) const {
    int centerX = (int) position.x;
    int centerY = (int) position.y;

    int outerRadius = radius * radius;
    int innerRadius = (radius - thickness) * (radius - thickness);
    for (int y = -radius; y <= radius; ++y) {
        for (int x = -radius; x <= radius; ++x) {
            int location = x * x + y * y;
            if (location <= outerRadius) {
                if (location > innerRadius) {
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
