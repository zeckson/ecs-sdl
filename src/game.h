//
// Created by Evgenii Shchepotev on 28.01.2024.
//

#ifndef RAYCASTING_GAME_H
#define RAYCASTING_GAME_H

#include <SDL2/SDL.h>
#include <memory>
#include "renderer/pixelrenderer.h"
#include "entity/entitymanager.h"

class Game {
public:
    const Uint16 width, height;
    void start();

protected:
    explicit Game(const char *title, Uint16 width, Uint16 height);


    std::shared_ptr<PixelRenderer> renderer;

    virtual bool onGameCreate() = 0;

    virtual bool onGameUpdate(double elapsedTime) = 0;
    virtual void onKeyDown(const SDL_Keysym &keysym) = 0;

private:
    SDL_Window *window;
    SDL_Renderer *pSDLRenderer;

    EntityManager manager;

    bool input();

    bool update(const float elapsedTime);

    Uint64 frame = 0;
};


#endif //RAYCASTING_GAME_H
