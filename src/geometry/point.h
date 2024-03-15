//
// Created by Evgenii Shchepotev on 15.03.2024.
//

#ifndef ECS_SDL_POINT_H
#define ECS_SDL_POINT_H


class Point {
public:
    const int x;
    const int y;

    explicit Point(): Point(0, 0) {}
    explicit Point(const int x, const int y): x(x), y(y) {}

};


#endif //ECS_SDL_POINT_H
