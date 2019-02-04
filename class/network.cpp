#include "./network.h"

void printVector(std::vector<auto> v) {
        std::cout << "{ ";
        for (size_t i = 0; i < v.size(); i++) {
                std::cout << v.at(i) << ' ';
        }
        std::cout << "}";
}

TensorNet::TensorNet() {
}

// TensorNet::TensorNet(const TensorNet &other) :
//         tensors(other.tensors),
//         network(other.network),
//         nbrTensors(other.nbrTensors),
//         nbrIndices(other.nbrIndices),
//         maxi(other.maxi),
//         maxID(other.maxID) {
// }

TensorNet::TensorNet(std::vector< std::vector<size_t> > Tnet, std::vector<Tensor> tens) {
        setTnet(Tnet);
        setTlist(tens);
        genMaxID();
}

TensorNet::~TensorNet() {
}


void TensorNet::setTnet(std::vector< std::vector<size_t> > Tnet) {
        nbrTensors = Tnet.size();
        tensors.resize(nbrTensors);
        nbrIndices = Tnet.at(0).size();  // every Tnet.at(i) has to have the same size
        network = Tnet;
}


void TensorNet::setTlist(std::vector<Tensor> tens) {
        tensors = tens;
}


size_t TensorNet::getNetwork(size_t tens, size_t idx) {
        return network.at(tens).at(idx);
}


void TensorNet::genMaxID() {
        maxi = 1;
        maxID.resize(nbrIndices);
        size_t indicesCounter = 0;
        for (size_t i = 0; i < nbrIndices; i++) {
                for (size_t k = 0; k < nbrTensors; k++) {
                        if (network[k][i] != 0) {
                                maxID.at(indicesCounter) = tensors.at(k).DimSize.at(getNetwork(k, i)-1);
                                maxi  *= maxID.at(indicesCounter);
                                indicesCounter++;
                                break;
                        }
                }
        }
        std::cout << "maxi: " << maxi<< '\n';
        std::cout << "maxID: ";
        for (size_t i = 0; i < nbrIndices; i++) {
                std::cout << "[" << maxID.at(i) << "]";
        }
        std::cout << "\n";
        return;
}


std::complex<double> TensorNet::calcVal() {
        std::vector<size_t> indices(nbrIndices, 0);
        std::complex<double> Tsum = 0;

        // Sum over all indices [i][j][a][b][g][f] like SUM_{i,j,a,b,g,f} C(g,a,i) * CONJG( C(g,b,j) ) * C(f,b,j) * CONJG( C(f,a,i) )
        for (size_t i = 0; i < maxi; i++) {
                // multiply Tensors for one indices combination [i][j][a][b][g][f] like C(g,a,i) * CONJG( C(g,b,j) ) * C(f,b,j) * CONJG( C(f,a,i) )
                std::complex<double> sumpart = 1;
                for (size_t j = 0; j < nbrTensors; j++) {
                        std::vector<size_t> idx(tensors.at(j).dimension, 0);
                        // generate indices to grab the Tensor entry
                        for (size_t k = 0; k < nbrIndices; k++) {
                                if (network.at(j).at(k) != 0) {
                                        idx.at(network.at(j).at(k) - 1) = indices.at(k);
                                }
                        }
                        // multyply tensors for one part of the sum
                        sumpart *= tensors.at(j).get(idx);
                }
                // add part of the sum to the sum
                Tsum += sumpart;

                // increase indices, to loop through them
                for (size_t j = 0; j < nbrIndices; j++) {
                        if (indices.at(j)+1 < maxID.at(j)) {
                                indices.at(j)++;
                                break;
                        } else {
                                indices.at(j) = 0;
                        }
                }
        }

        std::cout << "Calculated Tsum = "<< Tsum << "\n";
        Tsum /= maxi;
        std::cout << "Calculated Tsum / N= "<< Tsum << "\n";

        return 0.0;
}


std::complex<double> TensorNet::sampleTNet(std::vector<size_t> drawingOrder, std::vector<size_t> fromWhichTensor,
                                           std::vector<char> drawingType, std::vector<size_t> tracingID) {
        std::vector<size_t> idx(nbrIndices, 0);
        std::vector<double> weight(nbrTensors, 1);

        std::vector<size_t> sampleIDnext;
        size_t sampleTID = 0;
        size_t MaxNbrOfDrawings = *std::max_element(drawingOrder.begin(), drawingOrder.end());
        // std::cout << "MaxNbrOfDrawings:  " << MaxNbrOfDrawings << '\n';
        for (size_t i = 0; i <= MaxNbrOfDrawings; i++) {

                // std::cout << '\n';
                // std::cout << '\n';
                // std::cout << "sampleIDnext: ";
                for (size_t j = 0; j < nbrIndices; j++) {
                        if (drawingOrder.at(j) == i) {
                                // std::cout << j << " ";
                                sampleIDnext.push_back(j);
                        }
                }
                // std::cout << '\n';

                if (drawingType.at(sampleIDnext.at(0)) == 'u') {    // uniform drawing; weight doesn't has to be set
                        sampleTID = fromWhichTensor.at(sampleIDnext.at(0));
                        idx.at(sampleIDnext.at(0)) = tensors.at(sampleTID).getUniDistIndex(network.at(sampleTID).at(sampleIDnext.at(0))-1);

                } else if (drawingType.at(sampleIDnext.at(0)) == 't') {  // tracing
                        //  assume that sampleIDnext.size()  == 1
                        sampleTID = fromWhichTensor.at(sampleIDnext.at(0));
                        size_t sampleID = network.at(sampleTID).at(sampleIDnext.at(0))-1;
                        size_t sumID = network.at(sampleTID).at(tracingID.at(sampleIDnext.at(0)))-1;
                        // std::cout << sampleTID << ", " << sampleID << ", " << sumID << '\n';

                        // generate indices vector for tensor
                        std::vector<size_t> idxTen(tensors.at(sampleTID).dimension, 0);
                        for (size_t j = 0; j < nbrIndices; j++) {
                                if (network.at(sampleTID).at(j) != 0) {
                                        idxTen.at(network.at(sampleTID).at(j)-1) = idx.at(j);
                                }
                        }

                        // printVector(idxTen);
                        // std::cout << '\n';

                        tensors.at(sampleTID).getISampIndexTrace(sampleID, sumID, &idxTen);

                        // printVector(idxTen);
                        // std::cout << '\n';

                        idx.at(sampleIDnext.at(0)) = idxTen.at(sampleID);
                        weight.at(sampleTID) *= tensors.at(sampleTID).getISampProbTrace(sampleID, sumID, idxTen);

                        // printVector(idx);
                        // std::cout << '\n';
                        // printVector(weight);
                        // std::cout << '\n';
                        // std::cout << sampleTID << ", " << sampleID << ", " << sampleIDnext.at(0) << '\n';
                        // std::cout << network.at(sampleTID).at(sampleIDnext.at(0))-1 << '\n';

                        weight.at(sampleTID) *= tensors.at(sampleTID).DimSize.at(network.at(sampleTID).at(sampleIDnext.at(0))-1);

                } else if (drawingType.at(sampleIDnext.at(0)) == 'c') {  // compound drawing
                        //  assume that fromWhichTensor is the same for all idx in sampleIDnext
                        sampleTID = fromWhichTensor.at(sampleIDnext.at(0));

                        // generate number for combound distribution
                        size_t dist = 0b0;
                        for (size_t j = 0; j < sampleIDnext.size(); j++) {
                                dist += (0b1 << (network.at(sampleTID).at(sampleIDnext.at(j))-1));
                        }
                        dist -= 0b1;

                        // generate indices vector for tensor
                        std::vector<size_t> idxTen(tensors.at(sampleTID).dimension, 0);
                        for (size_t j = 0; j < nbrIndices; j++) {
                                if (network.at(sampleTID).at(j) != 0) {
                                        idxTen.at(network.at(sampleTID).at(j)-1) = idx.at(j);
                                }
                        }

                        tensors.at(sampleTID).getISampIndexComp(dist, &idxTen);

                        for (size_t j = 0; j < sampleIDnext.size(); j++) {
                                idx.at(sampleIDnext.at(j)) = idxTen.at(network.at(sampleTID).at(sampleIDnext.at(j))-1);
                                weight.at(sampleTID) *= tensors.at(sampleTID).DimSize.at(network.at(sampleTID).at(sampleIDnext.at(j))-1);
                        }
                        weight.at(sampleTID) *= tensors.at(sampleTID).getISampProbComp(dist, idxTen);
                }
                sampleIDnext.clear();
                // printVector(idx);
                // std::cout << "\n\n";
        }

        // std::cout << "\n\nWeights: ";
        // printVector(weight);
        // std::cout << '\n';
        // std::cout << "idx: ";
        // printVector(idx);
        // std::cout << "\n\n";

        // calculating value for sampled indices
        std::complex<double> T_part = 1;
        for (size_t t = 0; t < nbrTensors; t++) {
                std::vector<size_t> idxTen(tensors.at(t).dimension, 0);
                for (size_t i = 0; i < nbrIndices; i++) {
                        if (network.at(t).at(i) != 0) {
                                idxTen.at(network.at(t).at(i)-1) = idx.at(i);
                        }
                }
                T_part *= tensors.at(t).get(idxTen);
                T_part /= weight.at(t);
        }

        return T_part;
}
