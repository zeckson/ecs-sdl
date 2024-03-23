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
    Window win = {};
    while (fin.good() && !fin.eof()) {
        fin >> name;
        // TODO: rewrite to switch/case
        if (name == CONFIG_NAME(Window)) {
            fin >> win.width >> win.height >> win.fullscreen;
        } else {
            throw std::runtime_error("Unknown config type: " + name);
        }
    }

    fin.close();

    return Config(win);
}

std::ifstream &operator>>(std::ifstream &fin, Window &gameConfig) {
    if (!(fin >> gameConfig.width >> gameConfig.height >> gameConfig.fullscreen)) {
        fin.setstate(std::ios::failbit);
    }
    return fin;
}
