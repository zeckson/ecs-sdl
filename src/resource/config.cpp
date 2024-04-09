//
// Created by Evgenii Shchepotev on 22.03.2024.
//
#include <fstream>

#include "config.h"


Config Config::loadFromFile(const std::string &filename) {
    std::ifstream fin(filename);

    if (!fin) {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    std::string name;
    Window win{};
    Font font{};
    Assets assets{};
    while (fin.good() && !fin.eof()) {
        fin >> name;
        // TODO: rewrite to switch/case
        if (name == CONFIG_NAME(Window)) {
            fin >> win.width >> win.height >> win.fps >> win.fullscreen;
        } else if (name == CONFIG_NAME(Font)) {
            fin >> font.path >> font.size;
        } else if (name == CONFIG_NAME(Assets)) {
            std::string assetsPath;
            fin >> assetsPath;
            assets = loadAssetsConfig(assetsPath);
        } else {
            throw std::runtime_error("Unknown config type: " + name);
        }
    }

    fin.close();

    return Config(win, font, assets);
}

Assets Config::loadAssetsConfig(const std::string &path) {
    std::ifstream fin(path);

    if (!fin) {
        throw std::runtime_error("Failed to open file: " + path);
    }

    std::string name;
    Assets loaded = Assets();
    while (fin.good() && !fin.eof()) {
        fin >> name;
        if (name == "Texture") {
            std::string vPath;

            fin >> name >> vPath;
            loaded.textures[name] = vPath;
        } else if (name == "Font") {
            Font font;

            fin >> name >> font.path >> font.size;
            loaded.fonts[name] = font;
        } else if (name == "Animation") {
            AnimationConfig animationConfig;
            fin >> name >> animationConfig.textureName >> animationConfig.frames >> animationConfig.lifetime;
        } else {
            throw std::runtime_error("Unknown config type: " + name);
        }
    }

    fin.close();

    return loaded;
}
