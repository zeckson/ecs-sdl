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
    Player player{};
    Enemy enemy{};
    Bullet bullet{};
    while (fin.good() && !fin.eof()) {
        fin >> name;
        // TODO: rewrite to switch/case
        if (name == CONFIG_NAME(Window)) {
            fin >> win.width >> win.height >> win.fps >> win.fullscreen;
        } else if (name == CONFIG_NAME(Font)) {
            fin >> font.path >> font.size;
        } else if (name == CONFIG_NAME(Player)) {
            fin >> player.shapeRadius >> player.collisionRadius >> player.speed;
            fin >> player.fillColor >> player.outlineColor >> player.thickness;
        } else if (name == CONFIG_NAME(Enemy)) {
            fin >> enemy.shapeRadius.first >> enemy.shapeRadius.second;
            fin >> enemy.speed.first >> enemy.speed.second;
            fin >> enemy.outlineColor >> enemy.thickness;
            fin >> enemy.fragmentLifespan >> enemy.spawnInterval;
        } else if (name == CONFIG_NAME(Bullet)) {
            fin >> bullet.shapeRadius >> bullet.collisionRadius >> bullet.speed;
            fin >> bullet.fillColor >> bullet.outlineColor >> bullet.thickness;
            fin >> bullet.lifespan;
        } else {
            throw std::runtime_error("Unknown config type: " + name);
        }
    }

    fin.close();

    return Config(win, font, player, enemy, bullet);
}

std::ifstream &operator>>(std::ifstream &fin, Window &gameConfig) {
    if (!(fin >> gameConfig.width >> gameConfig.height >> gameConfig.fullscreen)) {
        fin.setstate(std::ios::failbit);
    }
    return fin;
}
