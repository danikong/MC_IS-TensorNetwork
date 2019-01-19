#include "./randomGen.h"

std::random_device Gen::seed_generator;
unsigned Gen::seed = seed_generator();
std::uniform_real_distribution<double> Gen::uni_real_Dist(0.0, 1.0);
std::mt19937 Gen::generator(Gen::seed);
