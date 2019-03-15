// Copyright 2018 BDan
//==================================
// include guard
#ifndef TENSOR_H_  // if x.h hasn't been included yet...
#define TENSOR_H_  // #define this so the compiler knows it has been included
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


struct Tensor {
        std::string filename = "";
        std::string identification = "";
        size_t dimension = 0;
        std::vector <size_t> DimSize;
        bool isComplexConj = false;

        size_t nbrEntries;
        std::vector < std::complex<double> >  Tens;

        // size_t size_TMag;  // size of TMag
        // double* TMag = NULL;

        std::vector<int*> idx_order;

        std::vector<size_t> w_samplingIdx;
        std::vector< std::vector< std::vector<double> > > compDist;
        std::vector< std::vector<std::vector< std::vector<double> > > > traceDist;
        std::vector< std::vector<double> > allTraceDist;
        std::vector<std::uniform_int_distribution<int>*> uniInt;

        Tensor();
        Tensor(std::string identifier, bool isCC);
        Tensor(std::string identifier, std::string fn, int dim, bool isCC);
        ~Tensor();

        void setDimProbaties(int dim, std::vector<size_t> DSize);
        void setDimension(int dim);
        void setDimSize(std::vector<size_t> DSize);
        void file2tensor(std::string fn, size_t dim);

        int Ten2Arr(std::vector<size_t> idx);
        std::vector<size_t> Arr2Ten(int pos);

        void set(std::vector<size_t> idx, std::complex<double> val);
        void set(int pos, std::complex<double> val);
        std::complex<double> get(std::vector<size_t> idx);
        std::complex<double> get(int pos);

        double mag(std::vector<size_t> idx);
        double mag(int pos);

        void printDimSize();

        // #################################################################
        // ################### HANDLING OF DISTRIBUTIONS ###################
        // #################################################################

        size_t distNbr(std::vector<size_t> samplingIdx);

        size_t compDistPos(size_t dist, std::vector<size_t> idx);
        size_t compDistPosIdx(size_t dist, std::vector<size_t> idx);
        void genCompDist();
        void getISampIndexComp(size_t dist, std::vector<size_t> *idx);
        double getISampProbComp(size_t dist, std::vector<size_t> idx);

        size_t traceDistPos(size_t dist, std::vector<size_t> idx);
        void posTraceDist(size_t dist, size_t id, std::vector<size_t> *idx);
        void genTraceDist();
        void genAllTraceDist();
        void getISampIndexTrace(size_t sampleID, size_t sumID, std::vector<size_t> *idx);
        double getISampProbTrace(size_t sampleID, size_t sumID, std::vector<size_t> idx);
        void getISampIndexAllTrace(size_t sampleID, std::vector<size_t> *idx);
        double getISampProbAllTrace(size_t sampleID, std::vector<size_t> idx);


        size_t getUniDistIndex(size_t id);
};


//=================================
#endif  // TENSOR_H_
//=================================
