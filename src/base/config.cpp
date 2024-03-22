//
// Created by Evgenii Shchepotev on 22.03.2024.
//
#include <fstream>

#include "config.h"


const Config &Config::loadFromFile(const std::string &filename) {
    std::ifstream fin(filename);

    if (!fin) {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    Config config{};
    std::string name;
    while (fin.good() && !fin.eof()) {
        fin >> name;
        // TODO: rewrite to switch/case
        if (name == GAMECONFIG_NAME) {
            fin >> config.gameConfig;
        }
    }

    fin.close();

    return config;
}

std::ifstream &operator>>(std::ifstream &fin, GameConfig &gameConfig) {
    if (!(fin >> gameConfig.width >> gameConfig.height >> gameConfig.fullscreen)) {
        fin.setstate(std::ios::failbit);
    }
    return fin;
}
