#include "sparc.hpp"
#include <iostream>

int main() {
    SPARC sparc;

    float **voltageMatrix;
    voltageMatrix = new float* [3];
    for (int i = 0; i < 3; i++) {
        voltageMatrix[i] = new float[3];
    }
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (i == 0) {
                voltageMatrix[i][j] = 0.0f;
            } else if (i == 1) {
                voltageMatrix[i][j] = 25.0f;
            } else {
                voltageMatrix[i][j] = 100.0f;
            }
        }
    }
    
    if (!sparc.uploadWaveform(voltageMatrix, 3, 3)) {
        return EXIT_FAILURE;
    }

    std::cout << "Success!" << std::endl;

    return EXIT_SUCCESS;
}