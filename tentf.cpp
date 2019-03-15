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


        std::string filename = "./MC_PA_Bartolot/Input_files/test/test1";

        Tensor t1("C1", filename, 3, false);
        t1.printDimSize();
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

        // std::cout << "#####################################"<< '\n';
        // std::cout << "### looking at generated compDist ###"<< '\n';
        // std::cout << "#####################################"<< '\n';
        //
        // std::cout << "DimSize: {";
        // for (size_t i = 0; i < t1.dimension; i++) {
        //         std::cout << t1.DimSize.at(i) << ' ';
        // }
        // std::cout << "}\n";
        //
        // for (size_t i = 0; i < t1.traceDist.at(2).at(1).at(7).size(); i++) {
        //         std::cout << t1.traceDist.at(2).at(1).at(7).at(i) << '\n';
        // }
        //
        // std::cout << "compDist:" << '\n';
        // std::cout << t1.compDist.size() << '\n';
        // for (size_t i = 0; i < t1.compDist.size(); i++) {
        //         std::bitset<8> x(i);
        //         std::cout << "  " << t1.compDist.at(i).size() << "  " << x << '\n';
        //         std::cout << "   ";
        //         for (size_t j = 0; j < t1.compDist.at(i).size(); j++) {
        //                 std::cout << t1.compDist.at(i).at(j).size() << "-";
        //         }
        //         std::cout << '\n';
        // }
        // // std::cout << t1.compDist.at(0).size() << '\n';
        //
        //
        //
        // std::cout << '\n';
        //
        // std::vector<size_t> idx = {0, 0, 0};
        // size_t dist = 0b0;
        // double prevVal = 0;
        // for (size_t i = 0; i < t1.compDist.at(dist).at(t1.compDistPos(dist, idx)).size(); i++) {
        //         idx.at(0) = i;
        //         printVector(idx);
        //         std::cout << ":  " << t1.compDist.at(dist).at(t1.compDistPos(dist, idx)).at(i) << " ";
        //         std::cout << t1.compDist.at(dist).at(t1.compDistPos(dist, idx)).at(i)-prevVal;
        //         std::cout << " " << t1.getISampProbComp(dist, idx) << '\n';
        //         prevVal = t1.compDist.at(dist).at(t1.compDistPos(dist, idx)).at(i);
        // }
        //
        // std::cout << '\n';
        // std::cout << '\n';
        // std::cout << '\n';
        //
        // std::cout << "############################"<< '\n';
        // std::cout << "### looking at traceDist ###"<< '\n';
        // std::cout << "############################"<< '\n';
        //
        // std::cout << "traceDist:" << '\n';
        // std::cout << t1.traceDist.size() << '\n';
        // for (size_t i = 0; i < t1.traceDist.size(); i++) {
        //         std::cout << "  " << t1.traceDist.at(i).size() << '\n';
        //         std::cout << "   ";
        //         for (size_t j = 0; j < t1.traceDist.at(i).size(); j++) {
        //                 std::cout << t1.traceDist.at(i).at(j).size() << "-";
        //         }
        //         std::cout << '\n';
        // }


        // std::cout << "###################################"<< '\n';
        // std::cout << "### Testing weight calculation ###"<< '\n';
        // std::cout << "##################################"<< '\n';
        //
        //
        // std::vector< std::vector<size_t> > net =  { {1, 2, 3, 0, 0, 0},    // 0  C(g,a,i)
        //                                             {1, 0, 0, 0, 2, 3},    // 1  CONJG( C(g,b,j) )
        //                                             {0, 0, 0, 1, 2, 3},    // 2  C(f,b,j)
        //                                             {0, 2, 3, 1, 0, 0} };  // 3  CONJG( C(f,a,i))
        // std::vector<Tensor> Tlist;
        // std::string filename = "./TenNet/test1";
        // Tlist.push_back(Tensor("C1", filename, 3, false));
        // Tlist.push_back(Tensor("C2", filename, 3, true));
        // Tlist.push_back(Tensor("C3", filename, 3, false));
        // Tlist.push_back(Tensor("C4", filename, 3, true));
        //
        // // std::vector<size_t> idxWhole = { 0, 1, 1, 4, 3, 3};
        // std::vector<size_t> idxWhole = {1, 1, 2, 5, 3, 0};
        // std::vector<size_t > idxtemp(3, 0);
        // std::vector<std::vector<size_t> > idx;
        // idx.resize(net.size());
        // for (size_t i = 0; i < net.size(); i++) {
        //         idx.at(i).resize(Tlist.at(i).dimension);
        // }
        // size_t dist = 0b0;
        //
        // for (size_t t = 0; t < net.size(); t++) {
        //         for (size_t i = 0; i < net.at(t).size(); i++) {
        //                 if (net.at(t).at(i) != 0) {
        //                         idx.at(t).at(net.at(t).at(i)-1) = idxWhole.at(i);
        //                 }
        //         }
        //         printVector(idx.at(t), std::to_string(t));
        // }
        //
        // std::vector<double> weight(Tlist.size(), 1);
        // std::complex<double> entry = 0;
        // printVector(weight, "Weight");
        // weight.at(0) *= Tlist.at(0).DimSize.at(0);
        // weight.at(0) *= Tlist.at(0).getISampProbComp(dist, idx.at(0));
        // weight.at(2) *= Tlist.at(2).DimSize.at(0);
        // weight.at(2) *= Tlist.at(2).getISampProbComp(dist, idx.at(2));
        // printVector(weight, "Weight");




        // std::cout << "############################"<< '\n';
        // std::cout << "### looking at AlltraceDist ###"<< '\n';
        // std::cout << "############################"<< '\n';
        //
        std::cout << "traceDist:" << '\n';
        std::cout << t1.allTraceDist.size() << '\n';
        for (size_t i = 0; i < t1.allTraceDist.size(); i++) {
                std::cout << "  " << t1.allTraceDist.at(i).size() << '\n';
        }
        std::cout << '\n';

        int dist = 0;
        for (size_t i = 0; i < t1.allTraceDist.at(dist).size(); i++) {
                std::cout << "   " << i << ": " << t1.allTraceDist.at(dist).at(i) << '\n';
        }

}
