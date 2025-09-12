//
// Created by Kirill Dulov on 9/12/25.
//

#ifndef NUMERIC_H
#define NUMERIC_H

inline bool IsPrime(const int n) {
    int amount = 1;
    for (int i = 2; i <= n; ++i) {
        if (n % i == 0) {
            amount ++;
        }
    }
    return amount == 2;
}

#endif //NUMERIC_H
