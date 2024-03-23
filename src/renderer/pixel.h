//
// Created by Evgenii Shchepotev on 28.01.2024.
//

#ifndef RAYCASTING_PIXEL_H
#define RAYCASTING_PIXEL_H

#include "SDL2/SDL.h"
#include <fstream>

class Pixel {
    Uint32 data;

    // ABGR
    static Uint32 pack(Uint8 r, Uint8 g, Uint8 b, Uint8 a) { return (r | g << 8 | b << 16 | a << 24); }

public:
    Pixel(const Uint8 r, const Uint8 g, const Uint8 b, const Uint8 a): data(Pixel::pack(r, g, b, a)) {}

    Pixel(const Uint8 r, const Uint8 g, const Uint8 b) : Pixel(r, g, b, 255) {}

    [[nodiscard]] Uint8 r() const {
        return data & 0xFF;
    };

    [[nodiscard]] Uint8 g() const {
        return data >> 8 & 0xFF;
    };

    [[nodiscard]] Uint8 b() const {
        return data >> 16 & 0xFF;
    };

    [[nodiscard]] Uint8 a() const {
        return data >> 24 & 0xFF;
    };

    Pixel operator/(const Uint8 value) const {
        return {Uint8(r() / value), Uint8(g() / value), Uint8(b() / value), Uint8(a() / value)};
    }

    Pixel operator*(const double value) const {
        return {Uint8(r() * value), Uint8(g() * value), Uint8(b() * value), Uint8(a() * value)};
    }

    void a(const Uint8 alpha);

    friend std::ifstream &operator>>(std::ifstream &infile, Pixel &pixel);
};

static const Pixel
        GREEN(0, 255, 0),
        RED(255, 0, 0),
        BLUE(0, 0, 255),
        YELLOW(255, 255, 0),
        WHITE(255, 255, 255),
        BLACK(0, 0, 0);


static const Pixel colorMap[] = {
        WHITE, YELLOW, RED, GREEN, BLUE
};

#endif //RAYCASTING_PIXEL_H
