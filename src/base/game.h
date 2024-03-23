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
#include "config.h"

#define ONE_SECOND 1000
#define FPS 60

struct FrameRate {
    explicit FrameRate(const int fps): maxFrameTime(double(double(ONE_SECOND) / double(fps))), fps(double(fps)) {};

    double const maxFrameTime;
    double fps = FPS;

    Uint64 totalFrame = 0;
    Uint16 frameCount = 0;
    Uint32 startTime = SDL_GetTicks();
    Uint32 frameStartTime = startTime;
    Uint32 currentFrameTime = startTime - 0;

    void frameStart();
    void frameEnd();
    void limit() const;
    void render(const std::shared_ptr<PixelRenderer> &renderer) const;

    [[nodiscard]] float elapsedTime() const;
};

class Game {
public:
    const Uint16 width, height;
    void start();
protected:
    explicit Game(const char *title, const Config &config);

    const Config config;

    FrameRate frameRate = FrameRate(config.window.fps);
    std::shared_ptr<PixelRenderer> renderer;

    virtual bool onGameCreate() = 0;
    virtual bool onGameUpdate(float elapsedTime) = 0;

    virtual void onKeyEvent(const SDL_Event &event) = 0;
    virtual void onMouseEvent(const SDL_Event &event) = 0;
private:
    App app;

    bool input();

};


#endif //RAYCASTING_GAME_H
