//
// Created by Evgenii Shchepotev on 28.03.2024.
//

#include "assetsmanager.h"

#include "SDL2/SDL_image.h"
#include "../resource/logger.h"

#include <fstream>
#include <format>
#include <cassert>


const AssetsManager AssetsManager::load(const std::string &filename) {
    AssetsManager assets;
    std::ifstream fin(filename);

    if (!fin) {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    std::string type;

    while (fin.good() && !fin.eof()) {
        fin >> type;
        // TODO: rewrite to switch/case
        if (type == TEXTURE_TYPE) {
            assets.loadTexture(fin);
        }
    }
    return assets;
}

void AssetsManager::loadTexture(std::ifstream &in) {
    std::string name;
    std::string path;
    in >> name >> path;

    Logger::info("Loading %s image from %s", name.c_str(), path.c_str());

    SDL_Surface *pSurface = IMG_Load(path.c_str());
    if (!pSurface) {
        throw std::runtime_error(std::format("Failed to load texture[{}]: {}", name, path));
    }

}

void AssetsManager::save(const std::string &name, SDL_Texture *sdlTexture) {
    assert(!assets[name]);

    assets[name] = sdlTexture;
}
