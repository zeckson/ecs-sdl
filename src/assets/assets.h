//
// Created by Evgenii Shchepotev on 28.03.2024.
//

#ifndef ECS_SDL_ASSETS_H
#define ECS_SDL_ASSETS_H

#include <string>
#include <map>
#include "animation.h"

#define TEXTURE_TYPE "Texture"

class Assets {
    std::map<std::string, Animation> assetMap;

    void loadTexture(std::ifstream &in);
public:
    explicit Assets() {}

    static const Assets load(const std::string &filename);
};


#endif //ECS_SDL_ASSETS_H
