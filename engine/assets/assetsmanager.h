//
// Created by Evgenii Shchepotev on 28.03.2024.
//

#ifndef ECS_SDL_ASSETSMANAGER_H
#define ECS_SDL_ASSETSMANAGER_H

#include <SDL_ttf.h>

#include <map>
#include <memory>
#include <string>

#include "animation.h"
#include "texture.h"

class AssetsManager {
  std::map<std::string, std::unique_ptr<Animation>> animations;
  std::map<std::string, std::unique_ptr<Texture>> textures;
  std::map<std::string, TTF_Font*> fonts;

 public:
  explicit AssetsManager() {}

  void addTexture(const std::string& name, SDL_Texture* texture, SDL_Surface* surface) {
    textures[name] = std::make_unique<Texture>(name, texture, surface);
  };
  void addFont(const std::string& name, TTF_Font* pFont) { fonts[name] = pFont; };

  const std::unique_ptr<Texture>& getTexture(const std::string& string) const;
  TTF_Font* getFont(const std::string& string) const;

  void quit();
};

#endif  // ECS_SDL_ASSETSMANAGER_H
