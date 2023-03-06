#include "sparc.hpp"
#include <iostream>

int main() {
    SPARC sparc;

    std::cout << +sparc.map_8_to_16(sparc.encodeVoltage(50.7f)) << std::endl;
    std::cout << +sparc.map_8_to_16(sparc.encodeVoltage(187.4f)) << std::endl;
    std::cout << +sparc.map_8_to_16(sparc.encodeVoltage(245.1f)) << std::endl;

    float voltageArray[100] = { 50.7f, 187.4, 245.1 };
    
    if (!sparc.uploadWaveform(voltageArray, 100)) {
        return EXIT_FAILURE;
    }

    std::cout << "Success!" << std::endl;

    return EXIT_SUCCESS;
}