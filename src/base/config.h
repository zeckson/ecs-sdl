//
// Created by Evgenii Shchepotev on 22.03.2024.
//

#ifndef ECS_SDL_CONFIG_H
#define ECS_SDL_CONFIG_H

#include <string>

// Define a macro to store the name of the struct as a string literal
#define CONFIG_NAME(Struct) #Struct

struct Window {
    int width;
    int height;

    bool fullscreen;
};

class Config {
    explicit Config(const Window &window): window(window) {};
public:
    const Window window;

    static Config loadFromFile(const std::string &filename);
};


#endif //ECS_SDL_CONFIG_H
