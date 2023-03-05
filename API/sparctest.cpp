#include "sparc.hpp"
#include <iostream>

int main() {
    SPARC sparc;
    if (!sparc.initializeSPARC()) {
        std::cout << "Failed initializing SPARC" << std::endl;
        return EXIT_FAILURE;
    }
    
    std::cout << "Initialized SPARC" << std::endl;

    for (auto item : sparc.voltageMap) {
        std::cout << item.first << " = " << +item.second << std::endl;
    }
    
    return EXIT_SUCCESS;
}