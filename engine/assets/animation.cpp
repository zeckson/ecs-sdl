//
// Created by Evgenii Shchepotev on 06.04.2024.
//

#include "animation.h"

Animation::Animation(const SDL_Texture* texturePointer) : texturePointer(texturePointer) {}

Animation::~Animation() { SDL_DestroyTexture(const_cast<SDL_Texture*>(texturePointer)); }
