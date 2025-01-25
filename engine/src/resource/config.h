//
// Created by Evgenii Shchepotev on 22.03.2024.
//

#ifndef ECS_SDL_CONFIG_H
#define ECS_SDL_CONFIG_H

#include <map>
#include <string>

#include "../renderer/pixel.h"
#include "assets.h"

// Define a macro to store the name of the struct as a string literal
#define CONFIG_NAME(Struct) #Struct

#define WIDTH 1280
#define HEIGHT 1024
#define FPS 60
#define FULLSCREEN 0

#define FONT_NAME "glitchgoblin"
#define FONT_PATH "gfx/font/glitchgoblin.ttf"
#define DEFAULT_FONT_SIZE 24

struct Window {
  int width = WIDTH;
  int height = HEIGHT;

  int fps = FPS;

  bool fullscreen = FULLSCREEN;
};

struct Font {
  std::string path = FONT_PATH;
  int size = DEFAULT_FONT_SIZE;
};

struct AnimationConfig {
  std::string textureName;

  int frames = 1;
  /*
   * 0 -- not animated
   * >0 -- how long to show each frame in animation
   */
  int lifetime = 0;
};

class Config {
  explicit Config(const Window& window, const Assets& assets) : window(window), assets(assets){};
  Config(const Window& window, const Font& font) : Config(window, Assets()){};

 public:
  const Window window;
  const Assets assets;

  static Config loadFromFile(const std::string& filename);
};

#endif  // ECS_SDL_CONFIG_H
