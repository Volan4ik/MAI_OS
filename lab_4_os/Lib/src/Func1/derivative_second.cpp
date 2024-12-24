#include "../../include/Func_1/derivative_second.hpp"
#include <cmath>

float Derivative(float A, float deltaX) {
    return (cos(A + deltaX) - cos(A - deltaX)) / (2 * deltaX);
}