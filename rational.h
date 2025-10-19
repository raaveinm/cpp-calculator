//
// Created by Kirill "Raaveinm" on 10/12/25.
//

#pragma once
#include <iosfwd>
#include <istream>
#include <numeric>
#include <string>

class Rational {
public:
    Rational() = default;
    Rational(const int numerator) : numerator_(numerator){}
    Rational(const int numerator, const int denominator)
        : numerator_(numerator), denominator_(denominator) { Reduction(); }
    Rational(const Rational& r) noexcept
        : numerator_(r.GetNumerator()), denominator_(r.GetDenominator()) {}

    Rational& operator=(const Rational& r) = default;

    inline Rational operator+(const Rational& r) const {
        return Rational(*this) += r;
    }
    inline Rational operator-(const Rational& r) const {
        return Rational(*this) -= r;
    }
    inline Rational operator*(const Rational& r) const {
        return Rational(*this) *= r;
    }
    inline Rational operator/(const Rational& r) const {
        return Rational(*this) /= r;
    }

    Rational operator+=(const Rational& r) {
        numerator_ = numerator_ * r.GetDenominator() + denominator_ * r.GetNumerator();
        denominator_ = denominator_ * r.GetDenominator();
        Reduction();
        return *this;
    }
    Rational operator-=(const Rational& r) {
        numerator_ = numerator_ * r.GetDenominator() - denominator_ * r.GetNumerator();
        denominator_ = denominator_ * r.GetDenominator();
        Reduction();
        return *this;
    }
    Rational operator*=(const Rational& r) {
        numerator_ *= r.GetNumerator();
        denominator_ *= r.GetDenominator();
        Reduction();
        return *this;
    }
    Rational operator/=(const Rational& r) {
        numerator_ *= r.GetDenominator();
        denominator_ *= r.GetNumerator();
        Reduction();
        return *this;
    }

    Rational operator++() {
        this->numerator_ += denominator_;
        return *this;
    }
    Rational operator--() {
        this->numerator_ -= denominator_;
        return *this;
    }
    Rational operator++(int) {
        Rational old = *this;
        this->numerator_ += denominator_;
        return old;
    }
    Rational operator--(int) {
        Rational old = *this;
        this->numerator_ -= denominator_;
        return old;
    }

    inline Rational operator+() const { return *this; }
    inline Rational operator-() const { return { -numerator_, denominator_ }; }

    inline Rational& operator=(const int val) {
        numerator_ = val;
        denominator_ = 1;
        return *this;
    }

    auto operator<=>(const Rational& r) const {
        return (numerator_ * r.denominator_) <=> (r.numerator_ * denominator_);
    }

    [[nodiscard]] Rational Inv() const {
        return {denominator_, numerator_};
    }

    [[nodiscard]] inline int GetNumerator() const { return numerator_; }
    [[nodiscard]] inline int GetDenominator() const { return denominator_; }

private:
    void Reduction() {
        if (denominator_ < 0) {
            numerator_ = -numerator_;
            denominator_ = -denominator_;
        }
        const int divisor = std::gcd(numerator_, denominator_);
        numerator_ /= divisor;
        denominator_ /= divisor;
    }

    int numerator_ = 0;
    int denominator_ = 1;
};

inline std::ostream & operator<<(std::ostream& os, const Rational& r) {
    const std::string num = std::to_string(r.GetNumerator());
    const std::string den = std::to_string(r.GetDenominator());
    if (r.GetDenominator() == 1) {
        os << num;
        return os;
    }
    os << num << std::string(" / ") << den;
    return os;
}

inline std::istream & operator>>(std::istream& is, Rational& r) {
    int num;
    if (!(is >> num)) {
        return is;
    }

    if (char separator = 0; is >> separator && separator == '/') {
        if (int den; is >> den && den != 0) {
            r = Rational(num, den);
        } else { is.setstate(std::ios_base::failbit); }
    } else {
        if (is) { is.putback(separator); }
        r = Rational(num);
    }
    return is;
}

inline bool operator==(const Rational& l, const Rational& r) {
    return (l.GetNumerator() == r.GetNumerator()) &&
           (l.GetDenominator() == r.GetDenominator());
}
