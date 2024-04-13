//
// Created by Evgenii Shchepotev on 06.04.2024.
//

#ifndef ECS_TEXTURE_H
#define ECS_TEXTURE_H

#include <SDL.h>
#include <string>

class Texture {
    const std::string name;
    const SDL_Texture *sdlTexture;
public:
    const int height;
    const int width;

    explicit Texture(const std::string &name, SDL_Texture *sdlTexture, SDL_Surface *surface);

    // Delete copy constructor
    Texture(const Texture &) = delete;

    // Delete move constructor
    Texture(Texture &&) = delete;

    // Delete copy assignment operator
    Texture &operator=(const Texture &) = delete;

    // Delete move assignment operator
    Texture &operator=(Texture &&) = delete;

    virtual ~Texture();

    SDL_Texture *texture() {
        return const_cast<SDL_Texture *>(sdlTexture);
    }
};


#endif //ECS_TEXTURE_H
