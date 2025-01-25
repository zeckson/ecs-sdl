//
// Created by Evgenii Shchepotev on 14.03.2024.
//

#ifndef ECS_SDL_APP_H
#define ECS_SDL_APP_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "../assets/assetsmanager.h"
#include "../resource/config.h"

class Game;

class App {
  explicit App(const char* title, const Config& config);

  SDL_Renderer* pSDLRenderer;
  SDL_Window* window;
  AssetsManager assetsManager = AssetsManager();

  SDL_Surface* loadSurface(const char* filename);

  SDL_Texture& loadTexture(const char* filename);

  void destroy();
  void loadAssets(const Assets& assets);
  
  friend class Game;
};

#endif  // ECS_SDL_APP_H
