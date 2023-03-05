#ifndef SPARC_HPP
#define SPARC_HPP

#include <cstdint>
#include <iostream>
#include <fstream>
#include <map>

class SPARC {
private:
    std::map<float, uint8_t> voltageMap; 
    
public:
    SPARC();
    ~SPARC() = default;
    bool initializeSPARC();
    uint16_t encodeVoltage(float voltage);
};

#endif