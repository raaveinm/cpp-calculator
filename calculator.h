//
// Created by Kirill "Raaveinm" on 9/12/25.
//

#ifndef CALCULATOR_H
#define CALCULATOR_H

#pragma once

#include <string>
#include <optional>
#include <cmath>
#include <sstream>
#include "rational.h"
#include "pow.h"

using Error = std::string;

template<typename T>
class Calculator {
public:
    std::optional<Error> Add(const T right);
    std::optional<Error> Sub(T right);
    std::optional<Error> Mul(T right);
    std::optional<Error> Div(T right);
    std::optional<Error> Pow(T right);

    void Set(T number){ current_res_ = number; is_init_ = true; }
    void Save() { saved_number_ = current_res_; }
    void Load();
    bool GetHasMem() const { return saved_number_.has_value(); }
    [[nodiscard]] std::string GetNumberRepr() const;
    T GetNumber() const { return current_res_; }

private:
    bool is_init_ = false;
    T current_res_;
    std::optional<T> saved_number_;

    static bool ReadNumber(T &result);
};

template<typename T>
std::optional<Error> Calculator<T>::Add(const T right) {
    current_res_ += right; is_init_ = true;
    return std::nullopt;
}

template<typename T>
std::optional<Error> Calculator<T>::Sub(const T right) {
    current_res_ -= right; is_init_ = true;
    return std::nullopt;
}

template<typename T>
std::optional<Error> Calculator<T>::Mul(const T right) {
    current_res_ *= right; is_init_ = true;
    return std::nullopt;
}

template<typename T>
std::optional<Error> Calculator<T>::Div(const T right) {
    if constexpr (!std::is_floating_point_v<T>) {
        if (right == static_cast<T>(0)) {
            return Error("Division by zero");
        }
    }
    if constexpr (std::is_same_v<T, Rational>) {
        if (current_res_.GetNumerator() == 0 && right.GetNumerator() == 0) {
            return Error("Division by zero");
        }
    }
    current_res_ /= right; is_init_ = true;
    return std::nullopt;
}

template<typename T>
std::optional<Error> Calculator<T>::Pow(const T right) {

    if constexpr (std::is_same_v<T, Rational>) {
        if (right.GetDenominator() != 1) {
            return Error("Fractional power is not supported");
        }

        if (current_res_.GetNumerator() == 0 && right.GetNumerator() == 0) {
            return Error("Zero power to zero");
        }

        current_res_ = RationalPow(current_res_, right);

    } else {
        if (current_res_ == static_cast<T>(0) && right == static_cast<T>(0)) {
            return Error("Zero power to zero");
        }

        if constexpr (std::is_integral_v<T> && !std::is_same_v<T, bool>) {
            if (right < 0) {
                return Error("Integer negative power");
            }
            current_res_ = IntegerPow(current_res_, right);

        } else if constexpr (std::is_same_v<T, float> || std::is_same_v<T, double>) {
            current_res_ = std::pow(current_res_, right);
        }
    }

    is_init_ = true;
    return std::nullopt;
}

template<typename T>
void Calculator<T>::Load() {
    if (saved_number_.has_value()) {
        current_res_ = saved_number_.value();
        is_init_ = true;
    }
}

template <typename T>
std::string Calculator<T>::GetNumberRepr() const {
    std::ostringstream tmp_str;
    tmp_str << current_res_;
    return tmp_str.str();
}

template<typename T>
bool Calculator<T>::ReadNumber(T &result) {
    return true;
}

#endif //CALCULATOR_H
