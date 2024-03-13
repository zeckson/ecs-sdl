//
// Created by Evgenii Shchepotev on 13.03.2024.
//

#ifndef ECS_SDL_VEC2_H
#define ECS_SDL_VEC2_H

template<typename T>
class Vec2 {
public:
    const T x;
    const T y;

    Vec2(): Vec2(0, 0) {}
    Vec2(const T x, const T y) : x(x), y(y) {}

};


#endif //ECS_SDL_VEC2_H
