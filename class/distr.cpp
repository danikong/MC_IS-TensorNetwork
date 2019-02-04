// Copyright 2018 BDan
#include "./distr.h"


void printVector(std::vector<auto> v) {
        std::cout << "{ ";
        for (size_t i = 0; i < v.size(); i++) {
                std::cout << v.at(i) << ' ';
        }
        std::cout << "}";
}

Distribution::Distribution(char distType, size_t distNbr, size_t size) {
        type = distType;
        samplingIdx = distNbr;
        dist.resize(size, 0);
}


Distribution::~Distribution() {
}






// #################################################################
// ################### HANDLING OF DISTRIBUTIONS ###################
// #################################################################

// do I still use this function ??????????? NOPE
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
        std::cout << "---->" << '\n';
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

        std::bitset<3> x(dist);
        std::cout << x << '\n';


        // reverse from upper to idx
        dist++;
        int shift = 1;
        for (size_t j = 0; j < dimension; j++) {
                if ( (dist & (0b1 << j)) != 0 ) {
                        shift *= DimSize.at(idx->size()-1-j);
                }
        }

        std::cout << "upper: " << upper << '\n';
        std::cout << "shift: " << shift << '\n';
        for (size_t j = dimension-1; j < dimension; j--) {
                std::cout << "j: " << j << "  " << dist << " & " << (0b1 << j) << " = " << (dist & (0b1 << j));
                if ( (dist & (0b1 << j)) != 0 ) {
                        shift /= DimSize.at(j);
                        // std::cout << "<----- \n";
                        std::cout << "   " << upper << " % " << shift << " -> " << (upper - upper%shift)/shift;
                        idx->at(j) = (upper - upper%shift)/shift;
                }
                std::cout << '\n';
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
        std::cout << "<----" << '\n';
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
