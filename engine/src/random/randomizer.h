//
// Created by Evgenii Shchepotev on 15.03.2024.
//

#ifndef ECS_SDL_RANDOMIZER_H
#define ECS_SDL_RANDOMIZER_H

#include "random/random.h"

class Randomizer {
 public:
  explicit Randomizer() { Random::initialize(); };

  int between(const int min, const int max) { return Random::getInt(min, max); }

  float betweenf(const float min, const float max) { return Random::getFloat(min, max); }

  int get(const int max) { return between(0, max); }

  float getf(const float max = 1) { return betweenf(0, max); }
};

#endif  // ECS_SDL_RANDOMIZER_H
