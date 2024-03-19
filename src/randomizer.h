//
// Created by Evgenii Shchepotev on 15.03.2024.
//

#ifndef ECS_SDL_RANDOMIZER_H
#define ECS_SDL_RANDOMIZER_H

#include <climits>
#include <cstdlib> // for rand() and srand()
#include <ctime>   // for time()

class Randomizer {
public:
    explicit Randomizer() {
        std::srand(std::time(nullptr)); // NOLINT(*-msc51-cpp)
    };

    int between(const int min = 0, const int max = INT_MAX) {
        return min + (std::rand() % (1 + max - min)); // NOLINT(*-msc50-cpp)
    }

    int get(const int max) {
        return std::rand() % (1 + max); // NOLINT(*-msc50-cpp)
    }

    // from 0..1
    float get() {
        return float(get(100)) / 100; // NOLINT(*-msc50-cpp)
    }

};


#endif //ECS_SDL_RANDOMIZER_H
