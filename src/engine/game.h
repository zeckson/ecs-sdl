//
// Created by Evgenii Shchepotev on 28.01.2024.
//

#ifndef RAYCASTING_GAME_H
#define RAYCASTING_GAME_H

#include <memory>
#include <map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "app.h"
#include "../renderer/pixelrenderer.h"
#include "../entity/entitymanager.h"
#include "../resource/config.h"
#include "../resource/assets.h"
#include "framerate.h"
#include "scene.h"

typedef std::map<std::string, std::shared_ptr<Scene>> SceneMap;

class Game {
public:
    const Uint16 width, height;

    void start();
    void changeScene(const std::string &name, const std::shared_ptr<Scene> scene);
    void quit() { running = false; }
protected:
    explicit Game(const char *title, const Config &config);

    const Config config;

    FrameRate frameRate = FrameRate(config.window.fps);
    std::unique_ptr<PixelRenderer> renderer;

    virtual bool onGameCreate() = 0;
    virtual void onGameUpdate() = 0;

    virtual void onKeyEvent(const SDL_Event &event) = 0;
    virtual void onMouseEvent(const SDL_Event &event) = 0;
private:
    App app;
    Assets assets;
    std::string currentScene;
    SceneMap scenes;

    bool running = true;

    bool input();

};


#endif //RAYCASTING_GAME_H
