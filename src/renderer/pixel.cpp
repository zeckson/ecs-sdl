//
// Created by Evgenii Shchepotev on 18.03.2024.
//

#include "pixel.h"

void Pixel::setAlpha(const Uint8 alpha) {
    data = (data & 0x00FFFFFF) | (alpha << 24);
}