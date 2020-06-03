#include "rectangle.hpp"

#include <iostream>

// Write you function here and test it with the main.

void Rectangle() {
    double n1, n2;
    std::cout << "Please enter width and height" << std::endl;
    std::cin >> n1 >> n2;
    std::cout << "Area: " << n1 * n2 << std::endl;
    std::cout << "Circumference: " << 2 * n1 + 2 * n2 << std::endl;
}

