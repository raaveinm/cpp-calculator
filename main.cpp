#include <iostream>
#include "numeric.h"

int main() {
    using namespace std::literals;

    int n;
    std::cin >> n;
    if (IsPrime(n)) {
        std::cout << "prime"s << std::endl;
    } else {
        std::cout << "not prime"s << std::endl;
    }
}
