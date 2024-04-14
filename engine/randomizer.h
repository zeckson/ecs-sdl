//
// Created by Evgenii Shchepotev on 15.03.2024.
//

#ifndef ECS_SDL_RANDOMIZER_H
#define ECS_SDL_RANDOMIZER_H

#include <climits>
#include <cstdlib>  // for rand() and srand()
#include <ctime>    // for time()

#define FLOAT_FRACTION 1000

class Randomizer {
 public:
  explicit Randomizer() {
    std::srand(std::time(nullptr));  // NOLINT(*-msc51-cpp)
  };

  int between(const int min, const int max) { return min + get(max - min); }

  float betweenf(const float min, const float max) { return min + getf(max - min); }

  int get(const int max) {
    return std::rand() % (1 + max);  // NOLINT(*-msc50-cpp)
  }

  // from 0..1
  float getf(const float max = 1) { return (float(get(FLOAT_FRACTION)) / FLOAT_FRACTION) * max; }
};

#endif  // ECS_SDL_RANDOMIZER_H
