#include "../../include/Func_1/derivative_first.hpp"
#include <cmath>

float Derivative(float A, float deltaX) {
    return (cos(A + deltaX) - cos(A)) / deltaX;
}