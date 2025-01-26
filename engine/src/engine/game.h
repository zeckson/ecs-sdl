//
// Created by Evgenii Shchepotev on 28.01.2024.
//

#ifndef RAYCASTING_GAME_H
#define RAYCASTING_GAME_H

#include <SDL.h>

#include "../assets/assetsmanager.h"
#include "../entity/entitymanager.h"
#include "../renderer/pixelrenderer.h"
#include "../resource/config.h"
#include "app.h"
#include "framerate.h"

class Game {
 public:
  const Uint16 width, height;
  const Config config;

  std::unique_ptr<PixelRenderer> renderer;

  void start();
  void quit() { running = false; }

  const AssetsManager& getAssetsManager() const { return app.assetsManager; }
  FrameRate frameRate = FrameRate(config.window.fps);

 protected:
  explicit Game(const char* title, const Config& config);

  // Return true -- if created successfully, false -- otherwise
  virtual bool onGameCreate() = 0;
  virtual void onGameUpdate() = 0;

  virtual void onKeyEvent(const SDL_Event& event) = 0;
  virtual void onMouseEvent(const SDL_Event& event) = 0;


 private:
  App app;

  bool running = true;

  bool input();
};

#endif  // RAYCASTING_GAME_H
