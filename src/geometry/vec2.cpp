//
// Created by Evgenii Shchepotev on 13.03.2024.
//

#include "vec2.h"

std::string Vec2::toString() const {
    std::stringstream ss;
    ss << "[" << x << ", " << y << "]";
    return ss.str();
}

void Vec2::operator+=(const Vec2 &rhs) {
    x += rhs.x;
    y += rhs.y;
}

void Vec2::operator-=(const Vec2 &rhs) {
    x -= rhs.x;
    y -= rhs.y;
}

void Vec2::operator*=(const float value) {
    x *= value;
    y *= value;
}

void Vec2::operator/=(const float value) {
    x /= value;
    y /= value;
}

Vec2 Vec2::normalize() const {
    float length = std::sqrt(x * x + y * y);
    return length != 0 ? Vec2{x / length, y / length} : Vec2{0, 0};
}

