#ifndef RENDERABLE_H
#define RENDERABLE_H

#include "SDL.h"

class Renderable {
public:
    explicit Renderable() {};
    virtual ~Renderable() {};

    virtual void render(SDL_Renderer* renderer) = 0;
};

#endif // RENDERABLE_H