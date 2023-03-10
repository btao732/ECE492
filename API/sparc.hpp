#ifndef SPARC_HPP
#define SPARC_HPP

#define MAX_VOLTAGE 300.0f

#include <cstdint>
#include <vector>
#include <map>

/*
Class for initializing and controlling SPARC arrays.
*/
class SPARC {
public:
    /*
    Lookup Table for converting float voltages to 
    an 8 bit representation.
    */
    std::map<float, uint8_t> voltageMap; 

    /*
    Function developed by Randy Palamar to generate
    appropriate 16 bit value from the 8 bit value,
    dependant on hardware architecture.
    */
    uint16_t map_8_to_16(uint8_t b);

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

    /*
    Upload voltage waveform for one channel to SPARC 
    system, takes an array of floats and size of the array.
    */
    bool uploadOneChannelWaveform(std::vector<float> voltages);

    /*
    Upload voltage waveform for n channels to SPARC 
    system, takes nchannels x len voltageMatrix.
    */
    bool uploadnChannelWaveform(std::vector<float> voltageMatrix);
};

#endif