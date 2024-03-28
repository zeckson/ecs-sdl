//
// Created by Evgenii Shchepotev on 18.03.2024.
//

#include "pixel.h"
#include <string>

Uint8 Pixel::r() const {
    return data & 0xFF;
}

Uint8 Pixel::g() const {
    return data >> 8 & 0xFF;
}

Uint8 Pixel::b() const {
    return data >> 16 & 0xFF;
}

Uint8 Pixel::a() const {
    return data >> 24 & 0xFF;
}

Pixel Pixel::operator/(const Uint8 value) const {
    return {Uint8(r() / value), Uint8(g() / value), Uint8(b() / value), Uint8(a() / value)};
}

Pixel Pixel::operator*(const double value) const {
    return {Uint8(r() * value), Uint8(g() * value), Uint8(b() * value), Uint8(a() * value)};
}

void Pixel::a(const Uint8 alpha) {
    data = (data & 0x00FFFFFF) | (alpha << 24);
}

// BC! It ignores alpha channel
std::ifstream &operator>>(std::ifstream &in, Pixel &pixel) {
    int r, g, b;
    in >> r >> g >> b;
    if (!(in.fail())) {
        pixel.data = Pixel::pack(r, g, b, 255);
    } else {
        // If reading fails, set the failbit of the input file stream
        throw std::runtime_error("Reading (R,G,B) failed");
    }
    return in;
}