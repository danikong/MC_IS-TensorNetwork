// #define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <random>
#include <complex>
#include <stdio.h>
// #include <mpi.h>

#include "./class/catch.hpp"
#include "./class/tensor.h"


TEST_CASE("tests for Tensorobject", "[factorial]") {
// int main() {
        std::string filename = "./TenNet/FTODDUMP_MC";
        Tensor t("C1", filename, 3, false);
        std::vector<size_t> idx;

        REQUIRE(t.dimension == 3);
        REQUIRE(t.DimSize.at(0) == 534);
        REQUIRE(t.DimSize.at(1) == 32);
        REQUIRE(t.DimSize.at(2) == 32);

        REQUIRE(t.nbrEntries == t.DimSize.at(0)*t.DimSize.at(1)*t.DimSize.at(2));
        REQUIRE(t.nbrEntries == 546816);

        REQUIRE(t.get(0) == std::complex<double> (0.932316437870E-08));
        idx = {1, 0, 0};
        REQUIRE(t.get(idx) == std::complex<double> (0.111930744632E-03 + 1.0i*0.297033015543E-03));
        idx = {44, 7, 10};
        REQUIRE(t.get(idx) == std::complex<double> (0.415876809506E-05 + 1.0i*0.408330357866E-04));

        // test linearization of indices
        idx = {0, 0, 0};
        REQUIRE(t.Ten2Arr(idx) == 0);
        for ( size_t i = 0; i < 100; i++ ) {
                idx = {rand() % 534, rand() % 32, rand() % 32};
                size_t array_index = t.Ten2Arr(idx);
                REQUIRE(array_index == idx.at(0)+idx.at(1)*534+idx.at(2)*534*32);
                REQUIRE(t.Arr2Ten(array_index) == idx);
        }

        // testing distribution numbering
        REQUIRE(t.distNbr(std::vector<size_t> {0, 1, 0}) == 1);
        REQUIRE(t.distNbr(std::vector<size_t> {0, 0, 1}) == 3);
        REQUIRE(t.distNbr(std::vector<size_t> {1, 1, 0}) == 2);

        // testing calculating distribution entries
        REQUIRE(t.compDistPos(0, std::vector<size_t> {13, 1, 0}) == t.compDistPos(0, std::vector<size_t> {213, 1, 0}));
        REQUIRE(t.compDistPos(2, std::vector<size_t> {10, 1, 7}) == 7);

        for (size_t i = 0; i < t.compDist.size(); i++) {
                for (size_t j = 0; j < t.compDist.at(i).size(); j++) {
                        // for (size_t k = 0; k < t.distributions.at(i).at(j).size(); k++) {
                        //         /* code */
                        // }
                        REQUIRE(t.compDist.at(i).at(j).back() == 1);
                }
        }
}
