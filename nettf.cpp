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

#include "./class/statMod.h"
#include "./class/network.h"

void printVector(std::vector<auto> v, std::string = "");

void printVector(std::vector<auto> v, std::string s) {
        if (s != "") {
                std::cout << s << ":  ";
        }
        std::cout << "{ ";
        for (size_t i = 0; i < v.size(); i++) {
                std::cout << v.at(i) << ' ';
        }
        std::cout << "}\n";
}

void printMatrix(std::vector<auto> v) {
        for (size_t i = 0; i < v.size(); i++) {
                printVector(v.at(i));
        }
        std::cout << '\n';
}

int main() {
        StatMod stat;

        // size_t nTensors = 4;
        // size_t nIndices = 6;
        // E= \sum_{i,j,a,b,g,f} C(g,a,i) * CONJG( C(g,b,j) ) * C(f,b,j) * CONJG( C(f,a,i) )

        // std::vector<Tensor*> Tlist(nTensors);
        std::vector<Tensor> Tlist;
        std::string filename = "./TenNet/test1";
        // filename = "./TenNet/test_is2";
        // filename = "./TenNet/test-4x2x2";
        // filename = "./TenNet/test-16x6x8";
        // filename = "./TenNet/FTODDUMP_MC";
        Tlist.push_back(Tensor("C1", filename, 3, false));
        Tlist.push_back(Tensor("C2", filename, 3, true));
        Tlist.push_back(Tensor("C3", filename, 3, false));
        Tlist.push_back(Tensor("C4", filename, 3, true));

        //                                           g  a  i  f  b  j
        //                                           0  1  2  3  4  5
        std::vector< std::vector<size_t> > net =  { {1, 2, 3, 0, 0, 0},    // 0  C(g,a,i)
                                                    {1, 0, 0, 0, 2, 3},    // 1  CONJG( C(g,b,j) )
                                                    {0, 0, 0, 1, 2, 3},    // 2  C(f,b,j)
                                                    {0, 2, 3, 1, 0, 0} };  // 3  CONJG( C(f,a,i))
        std::cout << "network: " << '\n';
        printMatrix(net);

        TensorNet Tnet(net, Tlist);

        std::cout << Tlist.size() << '\n';
        std::cout << net.size() << '\n';
        std::cout << net.at(0).size() << '\n';

        // ### 0 ###
        // std::vector<size_t> drawingOrder = {0, 1, 1, 4, 2, 3};
        // std::vector<size_t> fromWhichTensor = {0, 0, 0, 2, 2, 2};
        // std::vector<char> drawingType = {'u', 'c', 'c', 't', 'u', 'u'};
        // std::vector<size_t> tracingID = {0, 0, 0, 4, 0, 0};  // {0, 0, 0, 5, 0, 0} could also be used

        // ### 1 ###
        // std::vector<size_t> drawingOrder = {0, 1, 2, 3, 4, 5};
        // std::vector<size_t> fromWhichTensor = {0, 0, 0, 2, 2, 2};
        // std::vector<char> drawingType = {'u', 'u', 'u', 'u', 'u', 'u'};
        // std::vector<size_t> tracingID = {0, 0, 0, 4, 0, 0};  // {0, 0, 0, 5, 0, 0} could also be used

        // ### 2 ###
        // std::vector<size_t> drawingOrder = {2, 0, 1, 5, 3, 4};
        // std::vector<size_t> fromWhichTensor = {0, 0, 0, 2, 2, 2};
        // std::vector<char> drawingType = {'c', 'u', 'u', 'c', 'u', 'u'};
        // std::vector<size_t> tracingID = {0, 0, 0, 0, 0, 0};  // {0, 0, 0, 5, 0, 0} could also be used

        // ### 3 ###
        // std::vector<size_t> drawingOrder = {0, 1, 1, 2, 3, 3};
        // std::vector<size_t> fromWhichTensor = {0, 0, 0, 2, 2, 2};
        // std::vector<char> drawingType = {'u', 'c', 'c', 'u', 'c', 'c'};
        // std::vector<size_t> tracingID = {0, 0, 0, 0, 0, 0};

        // ### 4 ###
        std::vector<size_t> drawingOrder = {0, 1, 2, 4, 3, 5};
        std::vector<size_t> fromWhichTensor = {0, 0, 0, 2, 2, 2};
        std::vector<char> drawingType = {'u', 'u', 'u', 't', 'u', 'u'};
        std::vector<size_t> tracingID = {0, 0, 0, 5, 0, 0};

        printVector(drawingOrder, "drawingOrder   ");
        printVector(fromWhichTensor, "fromWhichTensor");
        printVector(drawingType, "drawingType    ");
        printVector(tracingID, "tracingID      ");

        std::size_t nbrOfSamples = 0;
        // nbrOfSamples = 534l*534l*32l;
        // nbrOfSamples *= 32l*32l;
        nbrOfSamples = 1;
        nbrOfSamples = 100000;

        std::cout << "nbrOfSamples = " << nbrOfSamples << '\n';
        int howManyOut = 10;
        int divider = nbrOfSamples/howManyOut;
        for (size_t i = 0; i < nbrOfSamples; i++) {
                std::complex<double> temp = Tnet.sampleTNet(drawingOrder, fromWhichTensor, drawingType, tracingID);
                stat.addOpt(temp);

                if ( ((i+1) % (divider) == 0 && i != 0) || i == 1 ) {
                        std::cout << (static_cast<int> ((i+1) / (divider))*(100/howManyOut)) << "%: ";
                        stat.mean_varOpt();
                        stat.var_of_varOpt();
                }


                // debug small number
                // std::cout << i << ": " << temp << "\n";
                // stat.mean_varOpt();
                // stat.var_of_varOpt();
        }


/*
        int tensor_ord[nTensors] = {3, 0, 1, 2};
        int nbr_is_idx = 3;
        int is_idx[nbr_is_idx] = {0, 3, 4};

        std::size_t nbrOfSamples = 0;
        // nbrOfSamples = 534l*534l*32l;
        // nbrOfSamples *= 32l*32l;
        // nbrOfSamples = 100000000;

        std::cout << "nbrOfSamples = " << nbrOfSamples << '\n';
        int howManyOut = 50;
        int divider = nbrOfSamples/howManyOut;
        for (size_t i = 0; i < nbrOfSamples; i++) {
                std::complex<double> temp = Tnet.sampleTNet(tensor_ord, is_idx, nbr_is_idx);
                stat.addOpt(temp);

                if ( ((i+1) % (divider) == 0 && i != 0) || i == 1 ) {
                        std::cout << (static_cast<int> ((i+1) / (divider))*(100/howManyOut)) << "%: ";
                        stat.mean_varOpt();
                        stat.var_of_varOpt();
                }


                // debug small number
                // std::cout << i << ": \n";
                // stat.mean_varOpt();
                // stat.var_of_varOpt();
        }

 */

        if (filename != "./TenNet_1/FTODDUMP_MC") {
                Tnet.calcVal();
        }
        return 0;
}
