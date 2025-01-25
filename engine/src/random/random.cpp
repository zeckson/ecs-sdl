//
// Created by Evgenii Shchepotev on 15.03.2024.
//

#include "random.h"

// Static member initialization
std::mt19937 Random::gen;
std::random_device Random::rd;

// Method to initialize the random number generator with a seed
void Random::initialize() {
    gen.seed(rd());  // Seed the generator with random_device
}

// Random Integer Generator (inclusive of min and max)
int Random::getInt(int min, int max) {
    std::uniform_int_distribution<> dist(min, max);  // Uniform distribution for integers
    return dist(gen);
}

// Random Float Generator (inclusive of min and max)
float Random::getFloat(float min, float max) {
    std::uniform_real_distribution<float> dist(min, max);  // Uniform distribution for floats
    return dist(gen);
}

// Random Double Generator (inclusive of min and max)
double Random::getDouble(double min, double max) {
    std::uniform_real_distribution<double> dist(min, max);  // Uniform distribution for doubles
    return dist(gen);
}
