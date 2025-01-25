#ifndef RANDOM_H
#define RANDOM_H

#include <random>

class Random {
private:
    static std::mt19937 gen;  // Static random number generator to be reused
    static std::random_device rd;  // Static random device to seed the generator

public:
    // Static method to initialize the random number generator
    static void initialize();

    // Random Integer Generator (inclusive of min and max)
    static int getInt(int min, int max);

    // Random Float Generator (inclusive of min and max)
    static float getFloat(float min, float max);

    // Random Double Generator (inclusive of min and max)
    static double getDouble(double min, double max);
};

#endif // RANDOM_H