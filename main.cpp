#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>

int CharToDigit(const char ch) {
    const std::vector chars = {'0','1','2','3','4','5','6','7','8','9','a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q','r','s','t','u','v','w','x','y','z'};
    for (int i = 0; i < chars.size(); i++) {
        if (tolower(ch) == chars.at(i)) {
            return i;
        }
    }
    return -1;
}

int StringToNumber(const std::string& s, const int base, bool& was_error) {
    if (base < 2 || base > 36) { was_error = true; return 0;}
    int dec_digit = 0;
    for (const char c : s) {
        if (CharToDigit(c) < 0 || CharToDigit(c) >= base) {
            was_error = true;
            return 0;
        }
        dec_digit = dec_digit * base + CharToDigit(c);
    }
    return dec_digit;
}

std::string NumberToString(int n, const int base) {
    if (base < 2 || base > 36) {
        return "";
    }
    std::string result;
    while (n > 0) {
        if (const int remainder = n % base; remainder < 10) {
            result += static_cast<char>(remainder + '0');
        } else {
            result += static_cast<char>(remainder - 10 + 'A');
        }
        n /= base;
    }
    std::reverse(result.begin(), result.end());
    return result;
}

std::string ConvertNotation(const std::string &number, const int from_base, const int to_base) {
    bool was_error = false;
    return NumberToString(StringToNumber(number, from_base,was_error), to_base);
}


int main() {
    using namespace std::literals;
    std::string src_string;
    int src_base, dst_base;

    std::cin >> src_string >> src_base >> dst_base;

    if (const auto result = ConvertNotation(src_string, src_base, dst_base); !result.empty()) {
        std::cout << result << std::endl;
    } else {
        std::cout << "ERROR"s << std::endl;
    }
    return 0;
}
