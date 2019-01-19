// Copyright 2018 BDan
#include "./tensor.h"

// ################################################################
// ################### GENERAL TENSOR FUNCTIONS ###################
// ################################################################

Tensor::Tensor() {
}


Tensor::Tensor(std::string identifier, bool isCC) {
        identification = identifier;
        isComplexConj = isCC;
        dimension = 0;
}


Tensor::Tensor(std::string identifier, std::string fn, int dim, bool isCC) {
        isComplexConj = isCC;
        identification = identifier;
        file2tensor(fn, dim);
}


Tensor::~Tensor() {
}


void Tensor::setDimProbaties(int dim, std::vector<size_t> DSize) {
        setDimension(dim);
        setDimSize(DSize);

        nbrEntries = 1;
        for (size_t j = 0; j < dimension; j++) {
                nbrEntries *= DimSize[j];
        }

        Tens.resize(nbrEntries);
        std::fill(Tens.begin(), Tens.end(), 0);

        idx_order.resize(dimension);
        w_samplingIdx.resize(dimension);
        for (size_t i = 0; i < dimension; i++) {
                idx_order.at(i) = new int[dimension];
                idx_order.at(i)[0] = i;
                w_samplingIdx.at(i) = std::pow(2, i);
                for (size_t j = 1; j < dimension; j++) {
                        idx_order.at(i)[j] = (j <= i ? j-1 : j);
                }
        }

        // setting size for compound distributions
        compDist.resize(std::pow(2, dimension)-1);
        int idx = 0;
        for (size_t i = 0; i < compDist.size(); i++) {
                int nbrOfDist = 1;
                idx += 0b1;
                for (size_t j = 0; j < dimension; j++) {
                        if ( ((idx) & (0b1 << j)) == 0b0 ) {
                                nbrOfDist *= DimSize.at(j);
                        }
                }
                compDist.at(i).resize(nbrOfDist);
        }
        idx = 0;
        for (size_t i = 0; i < compDist.size(); i++) {
                idx += 0b1;
                // std::cout << "i: " << i << "   nbrOfDist: " << compDist.at(i).size() << '\n';
                for (size_t j = 0; j < compDist.at(i).size(); j++) {
                        int distSize = 1;
                        for (size_t d = 0; d < dimension; d++) {
                                if ( ((idx) & (0b1 << d)) != 0b0 ) {
                                        distSize *= DimSize.at(d);
                                }
                        }
                        compDist.at(i).at(j).resize(distSize);
                        // std::cout << "   j: " << j << "   distSize: " << compDist.at(i).at(j).size() << '\n';
                }
        }


        // setting size for trace distributions
        traceDist.resize(dimension);
        for (size_t i = 0; i < traceDist.size(); i++) {
                traceDist.at(i).resize(dimension-1);
                for (size_t j = 0; j < traceDist.at(i).size(); j++) {
                        size_t j_real = j + (j >= i ? 1 : 0);
                        traceDist.at(i).at(j).resize(nbrEntries/DimSize.at(i)/DimSize.at(j_real));
                        for (size_t k = 0; k < traceDist.at(i).at(j).size(); k++) {
                                traceDist.at(i).at(j).at(k).resize(DimSize.at(i));
                                std::fill(traceDist.at(i).at(j).at(k).begin(), traceDist.at(i).at(j).at(k).end(), 0);
                        }
                }
        }
}

void Tensor::setDimension(int dim) {
        dimension = dim;
        // spDist.resize(dimension);
}

void Tensor::setDimSize(std::vector<size_t> DSize) {
        DimSize.resize(dimension);

        uniInt.resize(dimension);
        for (size_t i = 0; i < dimension; i++) {
                DimSize[i] = DSize[i];
                uniInt.at(i) = new std::uniform_int_distribution<int>(0, DimSize[i]-1);
        }
}


void Tensor::file2tensor(std::string fn, size_t dim) {
        filename = fn;
        std::ifstream in;
        in.open(filename.c_str());
        if (!in.is_open()) {
                std::cout << "READ went wrong!!!" << "\n";
                return;
        }

        if (!in) {
                std::cout << "Cannot open file.\n";
                return;
        }

        std::string line;
        getline(in, line);

        std::vector<size_t> DimensionSize;
        int TempDim;
        for (size_t i = 0; i < dim; i++) {
                in >> TempDim;
                DimensionSize.push_back(TempDim);
        }
        setDimProbaties(dim, DimensionSize);

        // std::cout << "{" << DimSize[0] << "," << DimSize[1] << "," << DimSize[2] <<"}" << '\n';

        getline(in, line);
        getline(in, line);

        //================ read in Tensor ================
        int idx;
        double x_val, y_val;
        for (size_t i = 0; i < nbrEntries; i++) {
                std::vector<size_t> index;
                in >> x_val >> y_val;
                for (size_t j = 0; j < dimension; j++) {
                        in >> idx;
                        index.push_back(idx-1);
                }
                if (isComplexConj) y_val *= -1;
                set(index, std::complex<double>(1.0*x_val + 1.0i*y_val) );
                // std::cout << "{" << index.at(0) << "," << index.at(1) << "," << index.at(2) <<"}" << '\n';
        }
        in.close();
        //================================================

        genCompDist();
        genTraceDist();
}

void Tensor::set(std::vector<size_t> idx, std::complex<double> val) {
        Tens[Ten2Arr(idx)] = val;
}

void Tensor::set(int pos, std::complex<double> val) {
        Tens[pos] = val;
}


std::complex<double> Tensor::get(std::vector<size_t> idx) {
        return Tens[Ten2Arr(idx)];
}

std::complex<double> Tensor::get(int pos) {
        return Tens[pos];
}

int Tensor::Ten2Arr(std::vector<size_t> idx) {
        int pos = 0;
        int shift = 1;

        for (size_t i = 0; i < dimension; i++) {
                pos += shift*idx.at(i);
                shift *= DimSize.at(i);
        }

        return pos;
}

std::vector<size_t> Tensor::Arr2Ten(int pos) {
        std::vector<size_t> idx;
        int mod = 1;
        for (size_t i = 0; i < dimension; i++) {
                idx.push_back((pos%(mod*DimSize.at(i))-pos%mod)/mod);
                mod *= DimSize.at(i);
        }
        return idx;
}

double Tensor::mag(std::vector<size_t> idx) {
        return std::abs(get(idx));
}

double Tensor::mag(int pos) {
        return std::abs(get(pos));
}


void Tensor::printDimSize() {
        std::cout << "DimSize: [ ";
        for (size_t i = 0; i < dimension; i++) {
                std::cout << DimSize.at(i) << " ";
        }
        std::cout << "]" << '\n';
}

// #################################################################
// ################### HANDLING OF DISTRIBUTIONS ###################
// #################################################################

size_t Tensor::distNbr(std::vector<size_t> samplingIdx) {
        size_t nbr = 0;
        for (size_t i = 0; i < dimension; i++) {
                nbr += samplingIdx.at(i)*w_samplingIdx.at(i);
        }
        nbr -= 1;
        return nbr;
}

size_t Tensor::compDistPos(size_t dist, std::vector<size_t> idx) {
        size_t pos = 0;
        size_t shift = 1;
        dist++;
        for (size_t j = 0; j < dimension; j++) {
                if ( ((~dist) & (0b1 << j)) != 0 ) {
                        pos += idx.at(j)*shift;
                        shift *= DimSize.at(j);
                }
        }
        return pos;
}

size_t Tensor::compDistPosIdx(size_t dist, std::vector<size_t> idx) {
        size_t pos = 0;
        size_t shift = 1;
        dist++;
        for (size_t j = 0; j < dimension; j++) {
                if ( (dist & (0b1 << j)) != 0 ) {
                        pos += idx.at(j)*shift;
                        shift *= DimSize.at(j);
                }
        }
        return pos;
}

void Tensor::genCompDist() {
        for (size_t i = 0; i < compDist.size(); i++) {
                for (size_t j = 0; j < compDist.at(i).size(); j++) {
                        std::fill(compDist.at(i).at(j).begin(), compDist.at(i).at(j).end(), 0);
                }
        }

        std::vector<size_t> idx = {0, 0, 0};
        for (size_t i = 0; i < nbrEntries; i++) {
                // add |C(idx)| to every distribution
                for (size_t j = 0; j < compDist.size(); j++) {
                        // std::cout << "j: " << j << "    compDistPos: " << compDistPos(j, idx) << "   compDistPosIdx: " << compDistPosIdx(j, idx) << '\n';
                        compDist.at(j).at(compDistPos(j, idx)).at(compDistPosIdx(j, idx)) += mag(i);
                }
                // increase tensor indices
                for (size_t j = 0; j < dimension; j++) {
                        if (idx.at(j)+1 < DimSize.at(j)) {
                                idx.at(j)++;
                                break;
                        } else {
                                idx.at(j) = 0;
                        }
                }
        }

        // generate cumulativ distribution out of density
        for (size_t i = 0; i < compDist.size(); i++) {
                for (size_t j = 0; j < compDist.at(i).size(); j++) {
                        for (size_t k = 1; k < compDist.at(i).at(j).size(); k++) {
                                compDist.at(i).at(j).at(k) += compDist.at(i).at(j).at(k-1);
                        }
                }
        }
        // normalize cumulativ distribution
        for (size_t i = 0; i < compDist.size(); i++) {
                for (size_t j = 0; j < compDist.at(i).size(); j++) {
                        for (size_t k = 0; k < compDist.at(i).at(j).size(); k++) {
                                compDist.at(i).at(j).at(k) /= compDist.at(i).at(j).back();
                        }
                }
        }
}

void Tensor::getISampIndexComp(size_t dist, std::vector<size_t> *idx) {
        double rand_uniform = Gen::uni_real_Dist(Gen::generator);
        int upper = compDist.at(dist).at(compDistPos(dist, *idx)).size()-1;
        int lower = -1;
        while (upper - lower > 1) {
                int mid = (upper+lower)/2;
                // std::cout << lower << "  -  " << mid << "  -  " << upper << '\n';
                if (rand_uniform < compDist.at(dist).at(compDistPos(dist, *idx)).at(mid)) {
                        upper = mid;
                } else {
                        lower = mid;
                }
        }

        // reverse from upper to idx
        dist++;
        int shift = 1;
        for (size_t j = 0; j < dimension; j++) {
                if ( (dist & (0b1 << j)) != 0 ) {
                        shift *= DimSize.at(j);
                }
        }

        // std::cout << "upper: " << upper << '\n';
        // std::cout << "shift: " << shift << '\n';
        for (size_t j = dimension-1; j < dimension; j--) {
                // std::cout << "j: " << j << "  " << dist << " & " << (0b1 << j) << " = " << (dist & (0b1 << j));
                if ( (dist & (0b1 << j)) != 0 ) {
                        shift /= DimSize.at(j);
                        // std::cout << "<----- \n";
                        // std::cout << "   " << upper << " % " << shift << " -> " << (upper - upper%shift)/shift;
                        idx->at(j) = (upper - upper%shift)/shift;
                }
                // std::cout << '\n';
        }

        // int shift = 1;
        // int pos = 0;
        // for (size_t j = 0; j < dimension; j++) {
        //         if ( ((dist+0b1) & (0b1 << j)) != 0 ) {
        //                 pos += idx.at(j)*shift;
        //                 shift *= DimSize.at(j);
        //         }
        // }
        // return idx;
        return;
}

double Tensor::getISampProbComp(size_t dist, std::vector<size_t> idx) {
        double prob = compDist.at(dist).at(compDistPos(dist, idx)).at(compDistPosIdx(dist, idx));
        if (compDistPosIdx(dist, idx) > 0) {
                prob -= compDist.at(dist).at(compDistPos(dist, idx)).at(compDistPosIdx(dist, idx)-1);
        }
        return prob;
}


size_t Tensor::traceDistPos(size_t dist, std::vector<size_t> idx) {
        size_t pos = 0;
        size_t shift = 1;
        for (size_t j = dimension; j < dimension; j--) {
                if ( (dist & (0b1 << j)) != 0 ) {
                        pos += idx.at(j)*shift;
                        shift *= DimSize.at(j);
                }
        }
        return pos;
}

void Tensor::posTraceDist(size_t dist, size_t id, std::vector<size_t> *idx) {
        size_t shift = 1;
        for (size_t i = 0; i < dimension; i++) {
                if ( (dist & (0b1 << i)) != 0 ) {
                        shift *= DimSize.at(i);
                }
        }
        for (size_t i = 0; i < dimension; i++) {
                if ( (dist & (0b1 << i)) != 0 ) {
                        shift /= DimSize.at(i);
                        idx->at(i) = (id - id%shift)/shift;
                }
        }

        return;
}

void Tensor::genTraceDist() {
        std::vector<size_t> idx(dimension, 0);
        std::fill(idx.begin(), idx.end(), 0);

        for (size_t i = 0; i < traceDist.size(); i++) {
                for (size_t j = 0; j < traceDist.at(i).size(); j++) {
                        size_t j_real = j + (j >= i ? 1 : 0);
                        int dist = ~((0b1 << i) + (0b1 << (j_real)));
                        for (size_t k = 0; k < traceDist.at(i).at(j).size(); k++) {
                                posTraceDist(dist, k, &idx);  // eval. idx which have to be given
                                for (size_t l = 0; l < traceDist.at(i).at(j).at(k).size(); l++) {
                                        idx.at(i) = l;
                                        for (size_t m = 0; m < DimSize.at(j_real); m++) {
                                                idx.at(j_real) = m;
                                                traceDist.at(i).at(j).at(k).at(l) += mag(idx);
                                        }
                                }
                        }
                }
        }

        // cumulativ
        for (size_t i = 0; i < traceDist.size(); i++) {
                for (size_t j = 0; j < traceDist.at(i).size(); j++) {
                        for (size_t k = 0; k < traceDist.at(i).at(j).size(); k++) {
                                for (size_t l = 1; l < traceDist.at(i).at(j).at(k).size(); l++) {
                                        traceDist.at(i).at(j).at(k).at(l) += traceDist.at(i).at(j).at(k).at(l-1);
                                }
                        }
                }
        }

        // normalization of distribution
        for (size_t i = 0; i < traceDist.size(); i++) {
                for (size_t j = 0; j < traceDist.at(i).size(); j++) {
                        for (size_t k = 0; k < traceDist.at(i).at(j).size(); k++) {
                                for (size_t l = 0; l < traceDist.at(i).at(j).at(k).size(); l++) {
                                        traceDist.at(i).at(j).at(k).at(l) /= traceDist.at(i).at(j).at(k).back();
                                }
                        }
                }
        }
}

void Tensor::getISampIndexTrace(size_t sampleID, size_t sumID, std::vector<size_t> *idx) {
        double rand_uniform = Gen::uni_real_Dist(Gen::generator);
        int upper = DimSize.at(sampleID);
        int lower = -1;
        while (upper - lower > 1) {
                int mid = (upper+lower)/2;
                if (rand_uniform < traceDist.at(sampleID).at(sumID).at(traceDistPos(~(0b1 << sampleID & 0b1 << sumID), *idx)).at(mid)) {
                        upper = mid;
                } else {
                        lower = mid;
                }
        }
        idx->at(sampleID) = upper;
        return;
}

double Tensor::getISampProbTrace(size_t sampleID, size_t sumID, std::vector<size_t> idx) {
        double prob = traceDist.at(sampleID).at(sumID).at(traceDistPos(~(0b1 << sampleID & 0b1 << sumID), idx)).at(idx.at(sampleID));
        if (idx.at(sampleID) > 0) {
                prob -= traceDist.at(sampleID).at(sumID).at(traceDistPos(~(0b1 << sampleID & 0b1 << sumID), idx)).at(idx.at(sampleID)-1);
        }
        return prob;
}


size_t Tensor::getUniDistIndex(size_t id) {
        return (*uniInt.at(id))(Gen::generator);
}
