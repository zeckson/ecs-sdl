//
// Created by Evgenii Shchepotev on 06.04.2024.
//

#ifndef ECS_TEXTURE_H
#define ECS_TEXTURE_H

#include <SDL2/SDL.h>
#include <string>

class Texture {
    const std::string name;
    const SDL_Texture* sdlTexture;
    int height;
    int width;
public:
    explicit Texture(std::string name, SDL_Texture *sdlTexture);

    virtual ~Texture();

};


#endif //ECS_TEXTURE_H
