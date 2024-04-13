//
// Created by Evgenii Shchepotev on 28.03.2024.
//

#ifndef ECS_SDL_FRAMERATE_H
#define ECS_SDL_FRAMERATE_H

#include <SDL.h>

#include "../renderer/pixelrenderer.h"

#define ONE_SECOND 1000
#define FPS 60

class FrameRate {

    double const maxFrameTime;
    double fps = FPS;

    Uint64 totalFrame = 0;
    Uint16 frameCount = 0;
    Uint32 startTime = SDL_GetTicks();
    Uint32 frameStartTime = startTime;
    Uint32 currentFrameTime = startTime - 0;

public:
    explicit FrameRate(const int fps): maxFrameTime(double(double(ONE_SECOND) / double(fps))), fps(double(fps)) {};

    void frameStart();
    void frameEnd();
    void limit() const;
    void render(const std::unique_ptr<PixelRenderer> &renderer) const;

    [[nodiscard]] float elapsedTime() const;
    [[nodiscard]] Uint64 currentFrame() const;
};


#endif //ECS_SDL_FRAMERATE_H
