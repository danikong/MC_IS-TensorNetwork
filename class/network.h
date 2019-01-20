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
// #include "./randomGen.h"

// variables

// functions
struct TensorNet {
        std::vector<Tensor> tensors;
        std::vector< std::vector<size_t> > network;
        size_t nbrTensors;
        size_t nbrIndices;

        size_t maxi;
        std::vector<size_t> maxID;

        TensorNet();
        // TensorNet(const TensorNet &);
        TensorNet(std::vector< std::vector<size_t> > Tnet, std::vector<Tensor> tens);
        // TensorNet(size_t nbrT, size_t nbrI, std::vector<std::vector<size_t> > Tnet, std::vector<Tensor> tens);
        ~TensorNet();

        void setTnet(std::vector<std::vector<size_t> > Tnet);
        void setTlist(std::vector<Tensor> tens);
        size_t getNetwork(size_t tens, size_t ind);

        void genMaxID();
        std::complex<double> calcVal();
        std::complex<double> sampleTNet(std::vector<size_t> drawingOrder, std::vector<size_t> fromWhichTensor,
                                        std::vector<char> drawingType, std::vector<size_t> tracingID);
        // std::complex<double> sampleTNet(std::vector<size_t> drawingOrder, std::vector<size_t> fromWhichTensor,
        // std::vector<char> drawingType, std::vector<size_t> tracingID(nbrIndices, 0));
};


//=================================
#endif  // FILE_NETWORK_H_
//=================================
