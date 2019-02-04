// Copyright 2018 BDan
//==================================
// include guard
#ifndef DISTR_H_  // if x.h hasn't been included yet...
#define DISTR_H_  // #define this so the compiler knows it has been included
//==================================

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <random>
#include <complex>
#include <bitset>
#include "./randomGen.h"


struct Distribution {
        char type = "";
        size_t samplingIdx;
        std::vector<double> dist;

        Distribution(char distType, size_t distNbr, size_t size);
        ~Distribution();
};


//=================================
#endif  // DISTR_H_
//=================================
