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

#include "./class/tensor.h"


void printV(std::vector<size_t> v) {
        for (std::vector<size_t>::const_iterator i = v.begin(); i != v.end(); ++i)
                std::cout << *i << ' ';
        std::cout << '\n';
}


void changeVec(std::vector<size_t> *v) {
        v->at(0) = 2;
        printV(*v);
}

int main() {
        // size_t b = 0b0;
        // std::bitset<8> x(b);
        // std::cout << x << '\n';
        // b += 0b1;
        // x = std::bitset<8>(b);
        // std::cout << x << '\n';
        //
        // size_t a = 1;
        // std::cout << std::bitset<8>(a << 4) << '\n';
        // a <<= 4;
        // std::cout << std::bitset<8>(a) << '\n';
        // std::cout << std::bitset<8>(0b1 << 4) << '\n';
        // std::cout << "-------------------" << '\n';
        //
        // std::string filename = "./TenNet/FTODDUMP_MC";
        // Tensor t("C1", filename, 3, false);
        // std::vector<size_t> idx = t.Arr2Ten(0);
        // for (auto i = idx.begin(); i != idx.end(); ++i)
        //         std::cout << *i << ' ';
        // std::cout << '\n';
        // std::vector<size_t> test_v = {0, 0, 0};
        // std::cout << (idx == std::vector<size_t>({0, 0, 0})) << '\n';
        //
        // std::cout << t.nbrEntries << '\n';
        //
        // std::cout << t.compDistPos(0, std::vector<size_t> {0, 0, 0}) << '\n';
        // std::cout << t.compDistPos(0, std::vector<size_t> {0, 1, 0}) << '\n';
        // std::cout << t.compDistPos(0, std::vector<size_t> {0, 10, 0}) << '\n';
        // std::cout << t.compDistPos(0, std::vector<size_t> {10, 1, 0}) << '\n';
        // std::cout << t.compDistPos(2, std::vector<size_t> {10, 1, 0}) << '\n';



        // for (size_t i = 0; i < t.distributions.at(0).at(0).size(); i++) {
        //         std::cout << i << "  " << t.distributions.at(0).at(0).at(i) << '\n';
        // }
        //
        // for (size_t i = 0; i < t.distributions.size(); i++) {
        //         for (size_t j = 0; j < t.distributions.at(i).size(); j++) {
        //                 // for (size_t k = 0; k < t.distributions.at(i).at(j).size(); k++) {
        //                 //         /* code */
        //                 // }
        //
        //         }
        // }



        Tensor t1("C1", "./TenNet/test1", 3, false);
        // t1.printDimSize();
        // std::cout << "\n" << '\n';
        // std::vector<size_t> v = {0, 1, 3};
        // printV(v);
        // t1.getISampIndexComp(2, &v);
        // printV(v);
        // t1.getISampIndexComp(2, &v);
        // printV(v);
        // t1.getISampIndexComp(2, &v);
        // printV(v);
        // t1.getISampIndexComp(2, &v);
        // printV(v);
        //
        // std::vector<size_t> distri = {0, 0, 0};
        // for (size_t i = 0; i < t.traceDist.at(distri.at(0)).at(distri.at(1)).at(distri.at(2)).size(); i++) {
        //         std::cout << t.traceDist.at(distri.at(0)).at(distri.at(1)).at(distri.at(2)).at(i) << '\n';
        // }

        std::cout << "DimSize: {";
        for (size_t i = 0; i < t1.dimension; i++) {
                std::cout << t1.DimSize.at(i) << ' ';
        }
        std::cout << "}\n";

        for (size_t i = 0; i < t1.traceDist.at(2).at(1).at(7).size(); i++) {
                std::cout << t1.traceDist.at(2).at(1).at(7).at(i) << '\n';
        }

}
