//
// Created by Evgenii Shchepotev on 06.04.2024.
//

#include "sprite.h"

Sprite::Sprite(const std::string& name, SDL_Texture* sdlTexture, int width, int height)
    : name(name), sdlTexture(sdlTexture), width(width), height(height) {}

Sprite::Sprite(const std::string& name, SDL_Texture* sdlTexture, SDL_Surface* surface)
    : Sprite(name, sdlTexture, surface->w, surface->h) {}

Sprite::~Sprite() {
}

const Vec2 Sprite::getBBox() const { return {width, height}; }

void Sprite::rotate(const double angleDeg) { Sprite::angle = angleDeg; }
