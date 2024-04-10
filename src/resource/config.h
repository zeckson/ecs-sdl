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

struct Assets {
    std::map<std::string, Font> fonts = {
            {FONT_NAME, Font {FONT_PATH, DEFAULT_FONT_SIZE}}
    };
    std::map<std::string, std::string> textures;
    std::map<std::string, AnimationConfig> animations;
};

class Config {
    explicit Config(const Window &window,
                    const Assets &assets) :
            window(window),
            assets(assets) {};
    Config(const Window &window, const Font &font) : Config(window, Assets()) {};

    static Assets loadAssetsConfig(const std::string &path);
public:
    const Window window;
    const Assets assets;

    static Config loadFromFile(const std::string &filename);
};

#endif //ECS_SDL_CONFIG_H
