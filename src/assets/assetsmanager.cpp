//
// Created by Evgenii Shchepotev on 28.03.2024.
//

#include "assetsmanager.h"

#include "../resource/logger.h"

#include <fstream>


void AssetsManager::quit() {
    Logger::info("Closing assets manager");

    for (const auto &it: fonts) {
        TTF_CloseFont(it.second);
    }

}

TTF_Font *AssetsManager::getFont(const std::string &name) const {
    return fonts.at(name);
}

const std::unique_ptr<Texture> &AssetsManager::getTexture(const std::string &name) const {
    return textures.at(name);
}

