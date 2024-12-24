#include "../../include/Func_2/e_series.hpp"

float factorial(int n) {
    float result = 1;
    for (int i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
}

float E(int x) {
    float sum = 0;
    for (int n = 0; n <= x; ++n) {
        sum += 1.0 / factorial(n);
    }
    return sum;
}