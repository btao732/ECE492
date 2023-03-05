#ifndef SPARC_HPP
#define SPARC_HPP

#define MAX_VOLTAGE 300.0f

#include <cstdint>
#include <iostream>
#include <fstream>
#include <map>

/*
Class for initializing and controlling SPARC arrays.
*/
class SPARC {
private:
    /*
    Lookup Table for converting float voltages to 
    an 8 bit representation.
    */
    std::map<float, uint8_t> voltageMap; 

public:
    /*
    Default constructor uses file "voltages.txt" to 
    generate voltageMap lookup table.
    */
    SPARC();

    /*
    Overrided constructor uses filename parameter to
    generate voltageMap lookup table, file must be of
    format '8_bit_representation mapped_voltage\n'.
    */
    SPARC(char *filename);

    /*
    Defaulted destructor.
    */
    ~SPARC() = default;
    
    /*
    Function takes float and converts to 8-bit 
    representation that is closest to the 
    desired voltage.
    */
    uint8_t encodeVoltage(float voltage);
};

#endif