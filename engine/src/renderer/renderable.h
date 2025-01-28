#ifndef RENDERABLE_H
#define RENDERABLE_H

#include "SDL.h"
#include <geometry/vec2.h>

class Renderable {
public:
    explicit Renderable() {};
    virtual ~Renderable() {};

    virtual void render(SDL_Renderer* renderer, const Vec2& dest) const = 0;
};

#endif // RENDERABLE_H