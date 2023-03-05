#include "sparc.hpp"
#include <iostream>

int main() {
    SPARC sparc;
    
    std::cout << "Initialized SPARC" << std::endl;

    std::cout << +sparc.encodeVoltage(12.6f) << std::endl;
    
    return EXIT_SUCCESS;
}