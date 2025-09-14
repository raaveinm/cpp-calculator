//
// Created by Kirill "Raaveinm" on 9/12/25.
//

#include "calculator.h"
#include <iostream>
#include <cmath>

bool Calculator::is_set = false;
Number Calculator::saved_number = 0.0;

bool Calculator::RunCalculatorCycle() {
    Number currentValue = 0.0;
    std::string command;

    if (!IsInitialCommandCorrect(currentValue)) return false;

    while (std::cin >> command) {
        double operand;

        if (command.empty()) {
            std::cerr << "Error: Numeric operand expected\n";
            return false;
        }

        switch (command[0]) {
            case '+':
                if (!(std::cin >> operand)) {
                    std::cerr << "Error: Numeric operand expected" << std::endl;
                    return false;
                }
                currentValue += operand;
                break;
            case 'q':
                return true;
            case '-':
                if (!(std::cin >> operand)) {
                    std::cerr << "Error: Numeric operand expected" << std::endl;
                    return false;
                }
                currentValue -= operand;
                break;
            case '*':
                if (command == "**") {
                    if (!(std::cin >> operand)) {
                        std::cerr << "Error: Numeric operand expected" << std::endl;
                        return false;
                    }
                    currentValue = std::pow(currentValue, operand);
                } else {
                    if (!(std::cin >> operand)) {
                        std::cerr << "Error: Numeric operand expected" << std::endl;
                        return false;
                    }
                    currentValue *= operand;
                }
                break;
            case '/':
                if (!(std::cin >> operand)) {
                    std::cerr << "Error: Numeric operand expected" << std::endl;
                    return false;
                }
                currentValue /= operand;
                break;
            case '=':
                std::cout << currentValue << std::endl;
                break;
            case 'c':
                currentValue = 0.0;
                break;
            case ':':
                if (!(std::cin >> operand)) {
                    std::cerr << "Error: Numeric operand expected" << std::endl;
                    return false;
                }
                currentValue = operand;
                break;
            case 's': //TODO
                Calculator().ReadNumber(currentValue);
                break;
            case 'l': //TODO
            {
                if (is_set) {
                    currentValue = GetSavedNumber();
                    break;
                }
                std::cerr << "Error: Memory is empty\n";
                return false;
            }


            default:
                std::cerr << "Error: Unknown token " << command << std::endl;
                return false;
        }
    }
    std::cerr << "Unexpected end of input\n";
    return false;
}

bool Calculator::IsInitialCommandCorrect(Number &currentValue) {
    if (!(std::cin >> currentValue)) {
        std::cerr << "Error: Numeric operand expected" << std::endl;
        return false;
    }
    return true;
}
/**
 *
 * if its read number - why did we give link to result?
 *
 * if its get and set - why did we name it so?
 *
 * if its set and get value in one time - why there is two commands ('s' and 'l')?
 *
 */
bool Calculator::ReadNumber(const Number &result) { //TODO
    SetSavedNumber(result);
    is_set = true;
    return true;
}