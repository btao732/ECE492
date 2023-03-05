#ifndef SPARC_HPP
#define SPARC_HPP

#define MAX_VOLTAGE 300.0f

#include <cstdint>
#include <iostream>
#include <fstream>
#include <map>

class SPARC {
private:
    std::map<float, uint8_t> voltageMap; 



public:
    SPARC();
    SPARC(char *filename);
    ~SPARC() = default;
    uint8_t encodeVoltage(float voltage);
};

#endif