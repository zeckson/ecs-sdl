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
#define PLAYER_SPEED 1.0 // Units / frame
#define PLAYER_FILL_COLOR {0, 0, 255}
#define PLAYER_OUTLINE_COLOR {0, 255, 0}
#define PLAYER_OUTLINE_THICKNESS 8

#define ENEMY_SHAPE_RADIUS_MIN 1 // x10
#define ENEMY_SHAPE_RADIUS_MAX 5 // x10
#define ENEMY_SPEED_MIN 2.0 // Units / frame
#define ENEMY_SPEED_MAX 4.0 // Units / frame
#define ENEMY_OUTLINE_COLOR {255, 0, 0}
#define ENEMY_THICKNESS 4
#define ENEMY_SPAWN_INTERVAL 1000 // Frames
#define ENEMY_FRAGMENTS_LIFESPAN 800 // Frames

#define BULLET_SHAPE_RADIUS 5
#define BULLET_SPEED 4.0 // Units / frame
#define BULLET_FILL_COLOR {255, 255, 255}
#define BULLET_OUTLINE_COLOR {0, 0, 0}
#define BULLET_OUTLINE_THICKNESS 0

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

struct Enemy {
    std::pair<int, int> shapeRadius = {ENEMY_SHAPE_RADIUS_MIN, ENEMY_SHAPE_RADIUS_MAX};
    std::pair<float, float> speed = {ENEMY_SPEED_MIN, ENEMY_SPEED_MAX};

    Pixel outlineColor = ENEMY_OUTLINE_COLOR;

    int thickness = ENEMY_THICKNESS;
    int fragmentLifespan = ENEMY_FRAGMENTS_LIFESPAN;
    int spawnInterval = ENEMY_SPAWN_INTERVAL;
};

struct Bullet {
    int shapeRadius = BULLET_SHAPE_RADIUS;
    int collisionRadius = BULLET_SHAPE_RADIUS;
    float speed = BULLET_SPEED;

    Pixel fillColor = BULLET_FILL_COLOR;
    Pixel outlineColor = BULLET_OUTLINE_COLOR;

    int thickness = BULLET_OUTLINE_THICKNESS;
};

class Config {
    explicit Config(const Window &window,
                    const Font &font,
                    const Player &player,
                    const Enemy &enemy,
                    const Bullet &bullet) :
            window(window),
            font(font),
            player(player),
            enemy(enemy),
            bullet(bullet) {};

public:
    const Window window;
    const Font font;
    const Player player;
    const Enemy enemy;
    const Bullet bullet;

    static Config loadFromFile(const std::string &filename);
};

#endif //ECS_SDL_CONFIG_H
