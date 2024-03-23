//
// Created by Evgenii Shchepotev on 22.03.2024.
//

#ifndef ECS_SDL_CONFIG_H
#define ECS_SDL_CONFIG_H

#include <string>
#include <map>
#include "../renderer/pixel.h"

// Define a macro to store the name of the struct as a string literal
#define CONFIG_NAME(Struct) #Struct

#define WIDTH 1280
#define HEIGHT 1024
#define FULLSCREEN 0

#define FONT_PATH "gfx/glitchgoblin.ttf"
#define DEFAULT_FONT_SIZE 24

struct Window {
    int width = WIDTH;
    int height = HEIGHT;

    bool fullscreen = FULLSCREEN;
};

struct Font {
    std::string path = FONT_PATH;
    int size = DEFAULT_FONT_SIZE;
};

class Config {
    explicit Config(const Window &window, const Font &font) : window(window), font(font) {};
public:
    const Window window;
    const Font font;

    static Config loadFromFile(const std::string &filename);
};


#endif //ECS_SDL_CONFIG_H
