#ifndef RANDOMGEN_HPP_  // if x.h hasn't been included yet...
#define RANDOMGEN_HPP_  // #define this so the compiler knows it has been included

#include <random>
// #include <vector>
// #include <iostream>

struct Gen {
        // private:
        static std::random_device seed_generator;
        static unsigned seed;
        static std::mt19937 generator;
        static std::uniform_real_distribution<double> uni_real_Dist;
};

#endif  // RANDOMGEN_HPP_
