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

void printV(std::vector<auto> v) {
        std::cout << "{ ";
        for (size_t i = 0; i < v.size(); i++) {
                std::cout << v.at(i) << ' ';
        }
        std::cout << "}";
}

void printA(auto v, size_t size) {
        for (int i = 0; i < size; i++)
                std::cout << v[i] << ' ';
        std::cout << '\n';
}

void changeVec(std::vector<size_t> *v) {
        v->at(0) = 2;
        printV(*v);
}

int main() {
        std::bitset<3> x(1);
        std::cout << x << '\n';
        x = x.to_ulong() + 1;
        std::cout << x << '\n';
        x.flip();
        std::cout << x << '\n';
        x.flip(1);
        std::cout << x << '\n';

        // size_t size = 3;
        // bool y[3] = {1, 0, 1};
        // printA(y, size);
        // y = !y;
        // printA(y, size);


        std::vector<bool> z = {
                1, 0, 1
        };
        printV(z);
        z.flip();
        printV(z);
        auto p = z.begin()._M_p;
        std::cout << *p << '\n';
        std::bitset<8> pp(*p);
        std::cout << pp << '\n';

}
