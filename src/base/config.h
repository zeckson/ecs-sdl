//
// Created by Evgenii Shchepotev on 22.03.2024.
//

#ifndef ECS_SDL_CONFIG_H
#define ECS_SDL_CONFIG_H

#include <string>

#define GAMECONFIG_NAME "Game"

struct GameConfig {
    int width;
    int height;

    bool fullscreen;

    // Declare the friend method inside the class
    friend std::ifstream& operator>>(std::ifstream& infile, GameConfig& config);
};

class Config {
public:
    GameConfig gameConfig;
    static const Config &loadFromFile(const std::string &filename);

};


#endif //ECS_SDL_CONFIG_H
