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
    char buffer[2] = {0};
    std::ofstream outputFile("waveformBinary.bin", std::ios::out | std::ios::binary);

    if (!outputFile) {
        std::cout << "Error opening waveformBinary.bin" << std::endl;
        return false;
    }

    for (int i = 0; i < n; i++) {
        uint16_t value = map_8_to_16(encodeVoltage(voltageArray[i]));
        buffer[0] = value; 
        buffer[1] = (value >> 8);
        outputFile.write(buffer, 2);
    }
    
    return true;
}

uint16_t SPARC::map_8_to_16(uint8_t b) {
    uint8_t i;
    uint16_t r;
    for (i = 0, r = 0; i < 8; i++) {
        r |= (b & (1 << i)) ? (1 << (2 * i)) : (1 << (2 * i + 1));
    }
    return r;
}