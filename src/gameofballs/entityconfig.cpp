//
// Created by Evgenii Shchepotev on 22.03.2024.
//
#include <fstream>

#include "entityconfig.h"


EntityConfig EntityConfig::loadFromFile(const std::string &filename) {
    std::ifstream fin(filename);

    if (!fin) {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    std::string name;
    Player player{};
    Enemy enemy{};
    Bullet bullet{};
    while (fin.good() && !fin.eof()) {
        fin >> name;
        // TODO: rewrite to switch/case
        if (name == CONFIG_NAME(Player)) {
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

    return EntityConfig(player, enemy, bullet);
}