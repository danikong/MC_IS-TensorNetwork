//==================================
// include guard
#ifndef NETWORK_H_  // if x.h hasn't been included yet...
#define NETWORK_H_  // #define this so the compiler knows it has been included
//==================================

// includes
#include <stdio.h>
// #include <mpi.h>
#include <vector>
#include <iostream>
#include <random>
#include <complex>
#include <algorithm>
#include "./tensor.h"
#include "./randomGen.h"

// variables

// functions
struct TensorNet {
        std::vector<Tensor*> tensors;
        std::vector<std::vector<size_t> > network;
        size_t nbrTensors;
        size_t nbrIndices;

        size_t maxi;
        std::vector<size_t> maxID;

        TensorNet();
        TensorNet(const TensorNet &);
        TensorNet(size_t nbrT, size_t nbrI, unsigned int **Tnet, std::vector<Tensor*> tens);
        ~TensorNet();

        void setTnet(size_t nbrT, size_t nbrI, unsigned int **Tnet);
        void setTlist(std::vector<Tensor*> tens);
        unsigned int getNetwork(size_t tens, size_t ind);

        void genMaxID();
        std::complex<double> calcVal();
        std::complex<double> sampleTNet(int* tensor_order, int* choose_uni, size_t size_choose_uni);
};


//=================================
#endif  // FILE_NETWORK_H_
//=================================
