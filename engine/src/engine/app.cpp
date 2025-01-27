//
// Created by Evgenii Shchepotev on 14.03.2024.
//

#include "app.h"

#include <SDL_ttf.h>

#include "../resource/logger.h"

App::App(const char* title, const Config& config) {
  Logger::logDefault()


  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not be initialized: %s", SDL_GetError());
  } else {
    printf("SDL video system is ready to go\n");
  }

  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

  // Create an application window with the following settings:
  int flags = SDL_WINDOW_SHOWN;
  const auto gameConfig = config.window;
  if (gameConfig.fullscreen) {
    flags |= SDL_WINDOW_FULLSCREEN;
  }
  window = SDL_CreateWindow(title,                   // window title
                            SDL_WINDOWPOS_CENTERED,  // initial x position
                            SDL_WINDOWPOS_CENTERED,  // initial y position
                            gameConfig.width,        // width, in pixels
                            gameConfig.height,       // height, in pixels
                            flags);

  // Check that the window was successfully created
  if (!window) {
    // In the case that the window could not be made...
    printf("Failed to open %d x %d window: %s\n", gameConfig.width, gameConfig.height, SDL_GetError());
    exit(1);
  }

  SDL_Renderer* sdlRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  if (!sdlRenderer) {
    printf("Failed to create renderer: %s\n", SDL_GetError());
    exit(1);
  }

  // Loading textures
  // Init img support
  if (!(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))) {
    printf("SDL_image initialization failed: %s\n", IMG_GetError());
    exit(1);
  }

  /* Initialize the TTF library */
  if (TTF_Init() < 0) {
    printf("Couldn't initialize TTF: %s\n", SDL_GetError());
    exit(1);
  }

  pSDLRenderer = sdlRenderer;

  loadAssets(config.assets);
}

SDL_Surface* App::loadSurface(const char* filename) {
  Logger::info("Loading surface %s", filename);

  SDL_Surface* pSurface = IMG_Load(filename);

  if (!pSurface) {
    Logger::error("Failed to load surface [%s] renderer: %s", filename, SDL_GetError());
  }

  return pSurface;
}

SDL_Texture& App::loadTexture(const char* filename) {
  SDL_Surface* pSurface = loadSurface(filename);

  SDL_Texture* texture = SDL_CreateTextureFromSurface(pSDLRenderer, pSurface);

  SDL_FreeSurface(pSurface);  // why surface wasn't allocated?

  if (!texture) {
    Logger::error("Failed to load texture [%s] renderer: %s", filename, SDL_GetError());
  }

  return *texture;
}

void App::destroy() {
  assetsManager.quit();
  TTF_Quit();

  SDL_DestroyRenderer(pSDLRenderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

void App::loadAssets(const Assets& assets) {
    for (const auto& it : assets.resources) {
    const auto resource = it.second.get();
    if (typeid(*resource) == typeid(Asset::Font))
    {
      const auto font = *dynamic_cast<Asset::Font*>(resource);
      const char* path = font.path.c_str();
      const int size = font.size;
      TTF_Font* fnt = TTF_OpenFont(path, size);
      if (!fnt) {
        Logger::error("Couldn't load %d pt font from %s: %s", size, path, SDL_GetError());
        // Handle font loading error
        exit(1);
      }
      assetsManager.addFont(it.first, fnt);
    }
    else if(typeid(*resource) == typeid(Asset::Sprite)) {
      const auto sprite = *dynamic_cast<Asset::Sprite*>(resource);
      const auto& name = sprite.name;
      const auto& path = sprite.path;

      const char* filename = path.c_str();

      SDL_Surface* pSurface = loadSurface(filename);
      SDL_Texture* texture = SDL_CreateTextureFromSurface(pSDLRenderer, pSurface);

      if (!texture) {
        Logger::error("Failed to load texture [%s] renderer: %s", path.c_str(), SDL_GetError());
      }

      // BC! Free all allocated resources inside assetsManager
      assetsManager.addTexture(name, texture, pSurface);
    }
  }
}
