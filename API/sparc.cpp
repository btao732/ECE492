#include "sparc.hpp"

SPARC::SPARC() {
    std::ifstream infile("voltages.txt");
    float voltage;
    uint8_t byte;
    
    if (!infile) {
        std::cout << "Error reading from file" << std::endl;
        exit(EXIT_FAILURE);
    }

    while (infile >> byte >> voltage) {
        voltageMap.insert(std::pair<float, uint8_t>(voltage, byte));
    }
}

bool SPARC::initializeSPARC() {
    return true;
}

uint16_t SPARC::encodeVoltage(float voltage) {
    return 0;
}