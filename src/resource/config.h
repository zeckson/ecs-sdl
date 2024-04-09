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
#define FPS 60
#define FULLSCREEN 0

#define FONT_NAME "glitchgoblin"
#define FONT_PATH "gfx/glitchgoblin.ttf"
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
    std::string name;
    std::string textureName;

    int frames = 1;
    int lifetime = 0; // 0 for static, otherwise frames to repeat
};

struct Assets {
    std::map<std::string, Font> fonts = {
            {FONT_NAME, Font {FONT_PATH, DEFAULT_FONT_SIZE}}
    };
    std::map<std::string, std::string> textures;
    std::map<std::string, AnimationConfig> animations;
};

class Config {
    explicit Config(const Window &window,
                    const Font &font,
                    const Assets &assets) :
            window(window),
            font(font),
            assets(assets) {};
    Config(const Window &window, const Font &font) : Config(window, font, Assets()) {};

public:
    const Window window;
    const Font font;
    const Assets assets;

    static Config loadFromFile(const std::string &filename);
};

#endif //ECS_SDL_CONFIG_H
