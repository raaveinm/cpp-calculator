//
// Created by Kirill "Raaveinm" on 9/24/25.
//

#ifndef UNTITLED_CALCULATOR_UI_H
#define UNTITLED_CALCULATOR_UI_H


#pragma once

#include <iostream>

#include "calculator.h"

class CalculatorUI {
public:
    // Реализуйте конструктор. Он должен сохранить ссылки
    // на потоки и калькулятор внутрь класса.
    // Используйте для этого список инициализации.
    CalculatorUI(Calculator& calc, std::ostream& out, std::ostream& err);

    bool Parse(std::istream& input) const;

private:
    bool ReadNumber(std::istream& input, Number& result) const;
    Calculator& calc_;
    std::ostream& out_;
    std::ostream& err_;
};

#endif //UNTITLED_CALCULATOR_UI_H