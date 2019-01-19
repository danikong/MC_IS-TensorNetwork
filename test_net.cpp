#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <random>
#include <complex>

#include "./class/catch.hpp"
// #include "./class/tensor.h"
#include "./class/network.h"
#include "./class/statMod.h"


TEST_CASE("Factorials are computed", "[factorial]") {
        StatMod stat;

        size_t nTensors = 4;
        size_t nIndices = 6;

        // E= \sum_{i,j,a,b,g,f} C(g,a,i) * CONJG( C(g,b,j) ) * C(f,b,j) * CONJG( C(f,a,i) )
        //                                 g, a, i, f, b, j
        int netw[nTensors][nIndices] =  { {1, 2, 3, 0, 0, 0},            // C(g,a,i)
                                          {1, 0, 0, 0, 2, 3},            // CONJG( C(g,b,j) )
                                          {0, 0, 0, 1, 2, 3},            // C(f,b,j)
                                          {0, 2, 3, 1, 0, 0} };          // CONJG( C(f,a,i))

        unsigned int **net;
        net = new unsigned int*[nTensors];
        for (size_t i = 0; i < nTensors; i++) {
                net[i] = new unsigned int[nIndices];
                for (size_t j = 0; j < nIndices; j++) {
                        net[i][j] = netw[i][j];
                }
        }

        std::vector<Tensor*> Tlist(nTensors);
        std::string filename = "./TenNet/test1";
        // filename = "./TenNet/test_is2";
        // filename = "./TenNet/test-4x2x2";
        // filename = "./TenNet/test-16x6x8";
        // filename = "./TenNet/FTODDUMP_MC";
        Tlist.at(0) = new Tensor("C1", filename, 3, false);
        Tlist.at(1) = new Tensor("C2", filename, 3, true);
        Tlist.at(2) = new Tensor("C3", filename, 3, false);
        Tlist.at(3) = new Tensor("C4", filename, 3, true);

        TensorNet Tnet =  TensorNet(nTensors, nIndices, net, Tlist);

        if (filename != "./TenNet_1/FTODDUMP_MC") {
                Tnet.calcVal();
        }
}
