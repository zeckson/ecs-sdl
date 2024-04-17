//
// Created by Evgenii Shchepotev on 06.04.2024.
//

#include "texture.h"

Texture::Texture(const std::string& name, SDL_Texture* sdlTexture, SDL_Surface* surface)
    : name(name), sdlTexture(sdlTexture), width(surface->w), height(surface->h) {}

Texture::~Texture() { SDL_DestroyTexture(const_cast<SDL_Texture*>(sdlTexture)); }
