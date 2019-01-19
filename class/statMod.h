//==================================
// include guard
#ifndef STATMOD_H_  // if x.h hasn't been included yet...
#define STATMOD_H_  // #define this so the compiler knows it has been included
//==================================

// includes
#include <iostream>
#include <complex>
#include <cmath>

// variables

// functions
struct StatMod {
        std::complex<double> sum_x;
        std::complex<double> sum_xx;
        double sum_x2;
        std::complex<double> sum_x3;
        double sum_x4;
        std::size_t M;  // number of samples

        // variables for recentering
        std::complex<double> mu_y;
        std::complex<double> sum_y;
        std::complex<double> sum_yy;
        double sum_y2;
        std::complex<double> sum_y3;
        double sum_y4;

        StatMod();
        ~StatMod();

        void add(std::complex<double> x);
        void addOpt(std::complex<double> x);
        void recentering();
        void mean_var();
        void mean_varOpt();
        std::complex<double> mean();
        std::complex<double> meanOpt();
        double var();
        double varOpt();
        void var_of_var();
        void var_of_varOpt();
};


//=================================
#endif  // STATMOD_H_
//=================================
