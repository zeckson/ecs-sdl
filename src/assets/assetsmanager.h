//
// Created by Evgenii Shchepotev on 28.03.2024.
//

#ifndef ECS_SDL_ASSETS_H
#define ECS_SDL_ASSETS_H

#include <string>
#include <map>
#include <memory>
#include <SDL_ttf.h>
#include "animation.h"
#include "texture.h"

#define TEXTURE_TYPE "Texture"

class AssetsManager {
    std::map<std::string, Animation> animations;
    std::map<std::string, std::unique_ptr<Texture>> textures;
    std::map<std::string, TTF_Font*> fonts;

    void loadTexture(std::ifstream &in);
public:
    explicit AssetsManager() {}

    void addTexture(std::string name, Texture texture) {
        textures[name] = std::make_unique<Texture>(texture);
    };


    static const AssetsManager load(const std::string &filename);

    void addFont(const std::string name, TTF_Font *pFont) {
        fonts[name] = pFont;
    };

    void quit();

    TTF_Font *getFont(const std::string &string) const;
};


#endif //ECS_SDL_ASSETS_H
