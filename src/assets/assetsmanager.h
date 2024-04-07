//
// Created by Evgenii Shchepotev on 28.03.2024.
//

#ifndef ECS_SDL_ASSETS_H
#define ECS_SDL_ASSETS_H

#include <string>
#include <map>
#include "animation.h"

#define TEXTURE_TYPE "Texture"

class AssetsManager {
    std::map<std::string, Animation> assetMap;
    std::map<std::string, SDL_Texture*> assets;

    void loadTexture(std::ifstream &in);
public:
    explicit AssetsManager() {}

    void save(const std::string &name, SDL_Texture* sdlTexture);

    static const AssetsManager load(const std::string &filename);
};


#endif //ECS_SDL_ASSETS_H
