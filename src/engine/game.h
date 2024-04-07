//
// Created by Evgenii Shchepotev on 28.01.2024.
//

#ifndef RAYCASTING_GAME_H
#define RAYCASTING_GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "app.h"
#include "../renderer/pixelrenderer.h"
#include "../entity/entitymanager.h"
#include "../resource/config.h"
#include "../assets/assetsmanager.h"
#include "framerate.h"
#include "scene.h"

class Game {
public:
    const Uint16 width, height;
    const Config config;

    void start();
    void quit() { running = false; }
protected:
    explicit Game(const char *title, const Config &config);


    FrameRate frameRate = FrameRate(config.window.fps);
    std::unique_ptr<PixelRenderer> renderer;

    virtual bool onGameCreate() = 0;
    virtual void onGameUpdate() = 0;

    virtual void onKeyEvent(const SDL_Event &event) = 0;
    virtual void onMouseEvent(const SDL_Event &event) = 0;
private:
    App app;
    AssetsManager assets;

    bool running = true;

    bool input();
};


#endif //RAYCASTING_GAME_H
