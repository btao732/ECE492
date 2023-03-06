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

bool SPARC::uploadWaveform(float voltageArray[], int n) {
    char buffer[1] = {0};
    std::ofstream outputFile("waveformBinary.bin", std::ios::out | std::ios::binary);

    if (!outputFile) {
        std::cout << "Error opening waveformBinary.bin" << std::endl;
        return false;
    }

    for (int i = 0; i < n; i++) {
        buffer[0] = encodeVoltage(voltageArray[i]);
        outputFile.write(buffer, 1);
    }
    
    return true;
}