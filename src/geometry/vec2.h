//
// Created by Evgenii Shchepotev on 13.03.2024.
//

#ifndef ECS_SDL_VEC2_H
#define ECS_SDL_VEC2_H

class Vec2 {
public:
    float x;
    float y;

    Vec2() : Vec2(0, 0) {}

    Vec2(const float x, const float y) : x(x), y(y) {}

    Vec2 operator+(const Vec2 &rhs) const { return {x + rhs.x, y + rhs.y}; }

};


#endif //ECS_SDL_VEC2_H
