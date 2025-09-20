#include "calculator.h"

#include <iostream>
#include <string>

constexpr int CALCULATION_ERROR = 1;

int main() {
    std::string type;
    std::cin >> std::ws;

    if (!Calculator::RunCalculatorCycle()) {
        std::cerr << "Program failed! Error code: " << CALCULATION_ERROR << std::endl;
    }
}