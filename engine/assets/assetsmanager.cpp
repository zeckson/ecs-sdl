//
// Created by Evgenii Shchepotev on 28.03.2024.
//

#include "assetsmanager.h"

#include <fstream>

#include "../resource/logger.h"
#include <cassert>

void AssetsManager::quit() {
  Logger::info("Closing assets manager");

  for (const auto& it : fonts) {
    TTF_CloseFont(it.second);
  }

  for (const auto& it : textures) {
    SDL_DestroyTexture(it.second);
  }

  for (const auto& it : surfaces) {
    SDL_FreeSurface(it.second);
  }
}

TTF_Font* AssetsManager::getFont(const std::string& name) const { return fonts.at(name); }

const std::unique_ptr<Sprite>& AssetsManager::getTexture(const std::string& name) const {
  assert(sprites.find(name) != sprites.end());
  return sprites.at(name);
}
