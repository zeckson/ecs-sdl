//
// Created by Evgenii Shchepotev on 28.01.2024.
//

#ifndef RAYCASTING_GAME_H
#define RAYCASTING_GAME_H

#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "app.h"
#include "../renderer/pixelrenderer.h"
#include "../entity/entitymanager.h"

#define ONE_SECOND 1000
#define FPS 60
#define DELAY_TIME (ONE_SECOND / FPS) // Delay time in milliseconds

struct FrameRate {
    Uint64 totalFrame = 0;
    Uint16 frameCount = 0;
    Uint32 startTime = SDL_GetTicks();
    Uint32 currentFrameTime = startTime - 0;
    double fps = FPS;

    void frameStart();
    void frameEnd();
    void limit() const;
    void render(const std::shared_ptr<PixelRenderer> &renderer) const;

    [[nodiscard]] float elapsedTime() const;

    Uint32 frameStartTime;
};

class Game {
public:
    const Uint16 width, height;
    void start();

protected:
    explicit Game(const char *title, Uint16 width, Uint16 height);

    std::shared_ptr<PixelRenderer> renderer;
    FrameRate frameRate;

    virtual bool onGameCreate() = 0;

    virtual bool onGameUpdate(float elapsedTime) = 0;
    virtual void onKeyDown(const SDL_Keysym &keysym) = 0;

private:
    App app;

    bool input();
};


#endif //RAYCASTING_GAME_H
