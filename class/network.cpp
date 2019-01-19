#include "./network.h"

void printArray(int *x, int count) {
        std::cout << "{ ";
        for (int i = 0; i < count; i++) {
                std::cout << x[i] << " ";
        }
        std::cout << "}";
}

TensorNet::TensorNet() {
}

TensorNet::TensorNet(const TensorNet &other) :
        tensors(other.tensors),
        network(other.network),
        nbrTensors(other.nbrTensors),
        nbrIndices(other.nbrIndices),
        maxID(other.maxID) {
}

TensorNet::TensorNet(size_t nbrT, size_t nbrI, std::vector< std::vector<size_t> > Tnet, std::vector<Tensor*> tens) {
        setTnet(nbrT, nbrI, Tnet);
        setTlist(tens);
        genMaxID();
}

TensorNet::~TensorNet() {
        if (network != NULL) {
                for (size_t i = 0; i < nbrTensors; i++) {
                        delete[] network[i];
                }
                delete[] network;
        }
        for (size_t i = 0; i < tensors.size(); i++) {
                delete tensors.at(i);
        }
}


void TensorNet::setTnet(size_t nbrT, size_t nbrI, std::vector< std::vector<size_t> > Tnet) {
        nbrTensors = nbrT;
        tensors.resize(nbrTensors);
        nbrIndices = nbrI;
        network = Tnet;
}


void TensorNet::setTlist(std::vector<Tensor*> tens) {
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
                                maxID.at(indicesCounter) = tensors.at(k)->DimSize.at(getNetwork(k, i)-1);
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
        std::vector<size_t> indices(nbrIndices, 80);
        std::complex<double> Tsum = 0;

        // Sum over all indices [i][j][a][b][g][f] like SUM_{i,j,a,b,g,f} C(g,a,i) * CONJG( C(g,b,j) ) * C(f,b,j) * CONJG( C(f,a,i) )
        for (size_t i = 0; i < maxi; i++) {
                // multiply Tensors for one indices combination [i][j][a][b][g][f] like C(g,a,i) * CONJG( C(g,b,j) ) * C(f,b,j) * CONJG( C(f,a,i) )
                std::complex<double> sumpart = 1;
                for (size_t j = 0; j < nbrTensors; j++) {
                        std::vector<size_t> idx(tensors.at(j)->dimension, 0);
                        // generate indices to grab the Tensor entry
                        for (size_t k = 0; k < nbrIndices; k++) {
                                if (network.at(j).at(k) != 0) {
                                        idx.at(network.at(j).at(k) - 1) = indices.at(k);
                                }
                        }
                        // multyply tensors for one part of the sum
                        sumpart *= tensors.at(j)->get(idx);
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
                                           std::vector<char> drawingType, std::vector<size_t> tracingID(nbrIndices, 0)) {
        std::vector<size_t> idx(nbrIndices, 0);
        std::vector<size_t> prob(nbrIndices, 1);

        // starting with all uniform drawings
        for (size_t i = 0; i < nbrIndices; i++) {
                if (drawingType.at(i) == 'u') {
                        idx.at(i) = tensors.at(fromWhichTensor(i)).getUniDistIndex(network.at(fromWhichTensor(i).at(i)));
                }
        }

        std::vector<int> sampleIDnext;
        int nbrOfDrawings = *std::max_element(drawingOrder.begin(), drawingOrder.end());
        for (size_t i = 0; i < nbrOfDrawings; i++) {
                for (size_t j = 0; j < nbrIndices; j++) {
                        if (drawingOrder.at(j) == i) {
                                sampleIDnext.push_back(j);
                        }
                }



                switch (drawingType.at(sampleIDnext.at(0))) {  // assume for ID to draw next the drawingtype is the same
                case 't':  // tracing
                        idxTen.resize(tensors.at(sampFromT).dimension)
                        for (size_t k = 0; k < tensors.at(sampFromT).dimension; k++) {
                                network.at(sampFromT).
                        }
                        getISampIndexTrace();
                case 'c': cout << '2';
                }
        }

        // weight[*t] *= tensors.at(*t)->getISampProb(network[*t][*i]-1, sampledTensor_id);
        // weight[*t] *= tensors.at(*t)->DimSize[network[*t][*i]-1];



        std::complex<double> c = 0;
        return c;
}
