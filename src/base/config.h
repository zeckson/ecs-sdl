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

#define FONT_PATH "gfx/glitchgoblin.ttf"
#define DEFAULT_FONT_SIZE 24

#define PLAYER_SHAPE_RADIUS 60
#define PLAYER_SPEED 1.0
#define PLAYER_FILL_COLOR {0, 0, 255}
#define PLAYER_OUTLINE_COLOR {0, 255, 0}
#define PLAYER_OUTLINE_THICKNESS 8

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

struct Player {
    int shapeRadius = PLAYER_SHAPE_RADIUS;
    int collisionRadius = PLAYER_SHAPE_RADIUS;
    float speed = PLAYER_SPEED;

    Pixel fillColor = PLAYER_FILL_COLOR;
    Pixel outlineColor = PLAYER_OUTLINE_COLOR;

    int thickness = PLAYER_OUTLINE_THICKNESS;
};

class Config {
    explicit Config(const Window &window, const Font &font, const Player &player) :
            window(window),
            font(font),
            player(player) {};

public:
    const Window window;
    const Font font;
    const Player player;

    static Config loadFromFile(const std::string &filename);
};

#endif //ECS_SDL_CONFIG_H
