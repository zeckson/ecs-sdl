//
// Created by Evgenii Shchepotev on 13.03.2024.
//

#include "vec2.h"

std::string Vec2::toString() const {
    std::stringstream ss;
    ss << "[" << x << ", " << y << "]";
    return ss.str();
}
