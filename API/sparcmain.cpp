#include "sparc.hpp"
#include <iostream>

int main() {
    SPARC sparc;
    
    std::cout << +sparc.map_8_to_16(0) << std::endl;
    std::cout << +sparc.map_8_to_16(50) << std::endl;
    std::cout << +sparc.map_8_to_16(200) << std::endl;

    std::cout << "Success!" << std::endl;

    return EXIT_SUCCESS;
}