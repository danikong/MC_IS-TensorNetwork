#include <iostream>
#include <vector>
#include <complex>
#include <string>
#include <sstream>
#include <ctime>

#include "./class/tensor.h"
// #include "./class/network.h"

int main() {
        // size_t nTensors = 4;
        // size_t nIndices = 6;

        std::string filename = "";
        filename = "./MC_PA_Bartolot/Input_files/large/FTODDUMP_MC";
        // filename = "./MC_PA_Bartolot/Input_files/small/FTODDUMP_MC";
        // Tensor C1("C1", filename, 3, false);  // C(g,a,i)
        // Tensor C2("C2", filename, 3, true);  // CONJG( C(g,b,j) )
        // Tensor C3("C3", filename, 3, false);  // C(f,b,j)
        // Tensor C4("C4", filename, 3, true);  // CONJG( C(f,a,i) )
        Tensor C1 = Tensor("C1", filename, 3, false);
        Tensor C2 = Tensor("C2", filename, 3, true);
        Tensor C3 = Tensor("C3", filename, 3, false);
        Tensor C4 = Tensor("C4", filename, 3, true);
        std::complex<double> E = 0;

        clock_t begin = clock();
        double elapsed_secs;
        clock_t end;


        end = clock();
        elapsed_secs = static_cast<double>(end - begin) / CLOCKS_PER_SEC;
        std::cout << "dt = " << elapsed_secs << '\n';
        begin = end;

        // ============= C -> V -> E =============
        Tensor V("V", false);
        Tensor VC("V", false);

        V.setDimension(C1.dimension+C2.dimension-2);
        VC.setDimension(C3.dimension+C4.dimension-2);
        // std::vector<size_t> setDimSizeV(C1.dimension+C2.dimension-2) = {
        std::vector<size_t> setDimSizeV = {
                C1.DimSize.at(1), C1.DimSize.at(2), C2.DimSize.at(1), C2.DimSize.at(2)
        };
        // std::vector<size_t> setDimSizeVC(C3.dimension+C4.dimension-2) = {
        std::vector<size_t> setDimSizeVC = {
                C4.DimSize.at(1), C4.DimSize.at(2), C3.DimSize.at(1), C3.DimSize.at(2)
        };

        V.setDimProbaties(C1.dimension+C2.dimension-2, setDimSizeV);
        VC.setDimProbaties(C3.dimension+C4.dimension-2, setDimSizeVC);


        std::cout << "{" << V.DimSize.at(0) << "," << V.DimSize.at(1) << ",";
        std::cout << V.DimSize.at(2) << "," << V.DimSize.at(2) << "}" << '\n';


        for (size_t a = 0; a < V.DimSize.at(0); a++) {
                for (size_t i = 0; i < V.DimSize.at(1); i++) {
                        for (size_t b = 0; b < V.DimSize.at(2); b++) {
                                for (size_t j = 0; j < V.DimSize.at(3); j++) {
                                        std::vector<size_t> idxV = {
                                                a, b, i, j
                                        };
                                        std::complex<double> V_val = 0;
                                        std::complex<double> VC_val = 0;
                                        for (size_t f = 0; f < C1.DimSize.at(0); f++) {
                                                std::vector<size_t> idxC = {
                                                        f, a, i
                                                };
                                                std::vector<size_t> idxCC = {
                                                        f, b, j
                                                };

                                                VC_val += C3.get(idxC)*C4.get(idxCC);

                                                V_val += C1.get(idxCC)*C2.get(idxC);
                                        }
                                        VC.set(idxV, VC_val);
                                        V.set(idxV, V_val);
                                }
                        }
                }
        }
        std::cout << "1" << '\n';
        for (size_t a = 0; a < V.DimSize.at(0); a++) {
                for (size_t b = 0; b < V.DimSize.at(2); b++) {
                        for (size_t i = 0; i < V.DimSize.at(1); i++) {
                                for (size_t j = 0; j < V.DimSize.at(3); j++) {
                                        std::vector<size_t> idxV = {
                                                a, b, i, j
                                        };
                                        E += V.get(idxV)*VC.get(idxV);
                                }
                        }
                }
        }
        std::cout << "V: E = " << E << '\n';
        // =======================================


        end = clock();
        elapsed_secs = static_cast<double>(end - begin) / CLOCKS_PER_SEC;
        std::cout << "dt = " << elapsed_secs << '\n';
        begin = end;
/*
        // ============= C -> K -> E =============
        Tensor K("V", false);
        Tensor KC("V", false);

        K.setDimension(C1.dimension+C4.dimension-4);
        KC.setDimension(C3.dimension+C2.dimension-4);
        int setDimSizeK[K.dimension] = {C1.DimSize[0], C4.DimSize[0]};
        int setDimSizeKC[KC.dimension] = {C3.DimSize[0], C2.DimSize[0]};

        K.setDimProbaties(K.dimension, setDimSizeK);
        KC.setDimProbaties(KC.dimension, setDimSizeKC);


        std::cout << "{" << K.DimSize[0] << "," << K.DimSize[1] << "}" << '\n';

        for (int f = 0; f < K.DimSize[0]; f++) {
                for (int g = 0; g < K.DimSize[1]; g++) {
                        std::complex<double> K_val = 0;
                        std::complex<double> KC_val = 0;
                        int idxK[K.dimension] = {f, g};
                        for (int a = 0; a < C1.DimSize[1]; a++) {
                                for (int i = 0; i < C1.DimSize[2]; i++) {
                                        int idxC[C1.dimension] = {g, a, i};
                                        int idxCC[C4.dimension] = {f, a, i};
                                        K_val += C1.get(idxC)*C4.get(idxCC);
                                        KC_val += C3.get(idxCC)*C2.get(idxC);
                                }
                        }
                        K.set(idxK, K_val);
                        KC.set(idxK, KC_val);
                }
        }
        E = 0;
        for (int f = 0; f < K.DimSize[0]; f++) {
                for (int g = 0; g < K.DimSize[1]; g++) {
                        int idxK[K.dimension] =  {f, g};
                        // int idxKC[K.dimension] =  {g, f};
                        E += K.get(idxK)*KC.get(idxK);
                }
        }
        std::cout << "K: E = " << E << '\n';
        // =======================================


        end = clock();
        elapsed_secs = static_cast<double>(end - begin) / CLOCKS_PER_SEC;
        std::cout << "dt = " << elapsed_secs << '\n';
        begin = end;


        E = 0;

        for (int j = 0; j < C2.DimSize[2]; j++) {
                for (int b = 0; b < C2.DimSize[1]; b++) {
                        for (int f = 0; f < C1.DimSize[0]; f++) {
                                for (int i = 0; i < C1.DimSize[2]; i++) {
                                        for (int a = 0; a < C1.DimSize[1]; a++) {
                                                for (int g = 0; g < C2.DimSize[0]; g++) {
                                                        int idxC_1[C1.dimension] = {g, a, i};
                                                        int idxC_2[C2.dimension] = {g, b, j};
                                                        int idxC_3[C3.dimension] = {f, b, j};
                                                        int idxC_4[C4.dimension] = {f, a, i};

                                                        E += C1.get(idxC_1)*C2.get(idxC_2)*C3.get(idxC_3)*C4.get(idxC_4);
                                                }
                                        }
                                }
                        }
                }
        }
        std::cout << '\n';
        std::cout << "C: E = " << E << '\n';

        end = clock();
        elapsed_secs = static_cast<double>(end - begin) / CLOCKS_PER_SEC;
        std::cout << "dt = " << elapsed_secs << '\n';

 */
        return 0;
}
