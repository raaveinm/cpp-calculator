//
// Created by Kirill "Raaveinm" on 9/12/25.
//

#include "calculator.h"


using namespace std::literals;

bool Calculator::ReadNumber(Number& result) {
    if (!(std::cin >> result)) {
        std::cerr << "Error: Numeric operand expected"s << std::endl;
        return false;
    }
    return true;
}

void Calculator::Add(const Number right) { current_res_ += right; is_init_ = true; }
void Calculator::Set(const Number number) { current_res_ = number; is_init_ = true; }
void Calculator::Sub(const Number right) { current_res_ -= right; is_init_ = true; }
void Calculator::Mul(const Number right) { current_res_ *= right; is_init_ = true; }
void Calculator::Div(const Number right) { current_res_ /= right; is_init_ = true; }
void Calculator::Pow(const Number right) { this->current_res_ = pow(current_res_, right); is_init_ = true; }
void Calculator::Save() { saved_number_ = current_res_; is_saved_ = true; }
bool Calculator::HasMem() const { return is_saved_; }
void Calculator::Load() { current_res_ = saved_number_; }
std::string Calculator::GetNumberRepr() const { return std::to_string(current_res_); }
Number Calculator::GetNumber() const { return current_res_; }

bool Calculator::RunCalculatorCycle() {
    Number init_number;
    if (!ReadNumber(init_number)) {
        return false;
    }

    Calculator calc;
    calc.Set(init_number);

    std::string token;
    while(std::cin >> token) {
        Number right;
        if (token == "+"s) {
            if (!ReadNumber(right)) {
                break;
            }
            calc.Add(right);
        } else if (token == "-"s) {
            if (!ReadNumber(right)) {
                break;
            }
            calc.Sub(right);
        } else if (token == "*"s) {
            if (!ReadNumber(right)) {
                break;
            }
            calc.Mul(right);
        } else if (token == "/"s) {
            if (!ReadNumber(right)) {
                break;
            }
            calc.Div(right);
        } else if (token == "**"s) {
            if (!ReadNumber(right)) {
                break;
            }
            calc.Pow(right);
        } else if (token == "s"s) {
            calc.Save();
        } else if (token == "l"s) {
            if (!calc.HasMem()) {
                std::cerr << "Error: Memory is empty"s << std::endl;
                break;
            }
            calc.Load();
        } else if (token == "="s) {
            std::cout << calc.GetNumberRepr() << std::endl;
        } else if (token == "c"s) {
            calc.Set(0);
        } else if (token == "n"s) {
            calc.Set(-calc.GetNumber());
        } else if (token == ":"s) {
            if (!ReadNumber(right)) {
                break;
            }
            calc.Set(right);
        } else if (token == "q"s) {
            return true;
        } else {
            std::cerr << "Error: Unknown token "s << token << std::endl;
            break;
        }
    }
    return false;
}