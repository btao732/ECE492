#include "sparc.hpp"

#include <cstdint>
#include <map>
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

bool SPARC::uploadOneChannelWaveform(std::vector<float> voltageArray) {
    char buffer[2] = {0};
    std::ofstream outputFile("waveform.bin", std::ios::out | std::ios::binary);

    if (!outputFile) {
        std::cout << "Error opening waveform.bin" << std::endl;
        return false;
    }

    for (int i = 0; i < voltageArray.size(); i++) {
        uint16_t value = map_8_to_16(encodeVoltage(voltageArray[i]));
        buffer[0] = (value >> 8); 
        buffer[1] = value;
        outputFile.write(buffer, 2);
    }
    
    return true;
}

bool SPARC::uploadnChannelWaveform(std::vector<float> voltageMatrix) {
    char buffer[2] = { 0 };
    std::ofstream outputFile("waveform.bin", std::ios::out | std::ios::binary);

    if (!outputFile) {
        std::cout << "Error opening waveform.bin" << std::endl;
        return false;
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