//
// Created by Evgenii Shchepotev on 06.04.2024.
//

#include "texture.h"

#include <utility>

Texture::Texture(std::string  name, SDL_Texture *sdlTexture): name(std::move(name)), sdlTexture(sdlTexture) {
    SDL_QueryTexture(sdlTexture, nullptr, nullptr, &width, &height);
}

Texture::~Texture() {
    SDL_DestroyTexture(const_cast<SDL_Texture*>(sdlTexture));
}
