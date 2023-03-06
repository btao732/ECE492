#include "sparc.hpp"
#include <iostream>

int main() {
    SPARC sparc;
    
    std::cout << "Initialized SPARC" << std::endl;

    std::cout << +sparc.encodeVoltage(12.6f) << std::endl;

    float voltageArray[100] = { 0.0f };
    
    if (!sparc.uploadWaveform(voltageArray, 100)) {
        return EXIT_FAILURE;
    }

    std::cout << "Success!" << std::endl;

    return EXIT_SUCCESS;
}