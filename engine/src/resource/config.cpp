//
// Created by Evgenii Shchepotev on 22.03.2024.
//
#include "config.h"

#include <fstream>

Config Config::loadFromFile(const std::string& filename) {
  std::ifstream fin(filename);

  if (!fin) {
    throw std::runtime_error("Failed to open file: " + filename);
  }

  std::string name;
  Window win{};
  Assets assets{};
  while (fin.good() && !fin.eof()) {
    fin >> name;
    // TODO: rewrite to switch/case
    if (name == CONFIG_NAME(Window)) {
      fin >> win.width >> win.height >> win.fps >> win.fullscreen;
    } else if (name == CONFIG_NAME(Assets)) {
      std::string assetsPath;
      fin >> assetsPath;
      assets = Assets::load(assetsPath);
    } else {
      throw std::runtime_error("Unknown config type: " + name);
    }
  }

  fin.close();

  return Config(win, assets);
}
