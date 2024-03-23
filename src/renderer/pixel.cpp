//
// Created by Evgenii Shchepotev on 18.03.2024.
//

#include "pixel.h"

void Pixel::setAlpha(const Uint8 alpha) {
    data = (data & 0x00FFFFFF) | (alpha << 24);
}

// BC! It ignores alpha channel
std::ifstream &operator>>(std::ifstream &in, Pixel &pixel) {
    int r, g, b;
    if (!(in >> r >> g >> b)) {
        pixel.data = Pixel::pack(r, g, b, 255);
    } else {
        // If reading fails, set the failbit of the input file stream
        in.setstate(std::ios::failbit);
    }
    return in;
}