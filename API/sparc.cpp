#include "sparc.hpp"

SPARC::SPARC() {
    std::ifstream infile("voltages.txt");
    float voltage;
    int byte;
    
    if (!infile) {
        std::cout << "Error reading from file" << std::endl;
        exit(EXIT_FAILURE);
    }

    while (infile >> byte >> voltage) {
        voltageMap.insert(std::pair<float, uint8_t>(voltage, byte));
    }
}

SPARC::SPARC(char *filename) {
    std::ifstream infile(filename);
    float voltage;
    int byte;
    
    if (!infile) {
        std::cout << "Error reading from file" << std::endl;
        exit(EXIT_FAILURE);
    }

    while (infile >> byte >> voltage) {
        voltageMap.insert(std::pair<float, uint8_t>(voltage, byte));
    }
}

uint8_t SPARC::encodeVoltage(float voltage) {
    float delta = MAX_VOLTAGE;
    float key;
    for (auto item : voltageMap) {
        float newDelta = voltage - item.first;
        if (fabsf(newDelta) < fabsf(delta)) {
            delta = newDelta;
            key = item.first;
        }
    }

    return voltageMap[key];
}