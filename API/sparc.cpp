#include "sparc.hpp"

#include <math.h>
#include <iostream>
#include <fstream>

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
    float closestVoltage;
    for (auto item : voltageMap) {
        float newDelta = voltage - item.first;
        if (fabsf(newDelta) < fabsf(delta)) {
            delta = newDelta;
            closestVoltage = item.first;
        }
    }

    return voltageMap[closestVoltage];
}