#include "sparc.hpp"
#include <iostream>

int main() {
    SPARC sparc;

    float voltageArray[100] = { 50.7f, 187.4, 245.1 };
    
    if (!sparc.uploadWaveform(voltageArray, 100)) {
        return EXIT_FAILURE;
    }

    std::cout << "Success!" << std::endl;

    return EXIT_SUCCESS;
}