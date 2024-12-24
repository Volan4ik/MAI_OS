#include <iostream>
#include "../Lib/include/Func_1/derivative_first.hpp"
#include "../Lib/include/Func_2/e_formule.hpp"

int main() {
    int command;
    while (true) {
        std::cout << "Enter command (1 for Derivative, 2 for E, 0 to exit): ";
        std::cin >> command;

        if (command == 0) {
            break;
        } else if (command == 1) {
            float A, deltaX;
            std::cout << "Enter A and deltaX: ";
            std::cin >> A >> deltaX;
            std::cout << "Derivative at " << A << " with deltaX " << deltaX << " is " << Derivative(A, deltaX) << std::endl;
        } else if (command == 2) {
            int x;
            std::cout << "Enter x: ";
            std::cin >> x;
            std::cout << "E(" << x << ") = " << E(x) << std::endl;
        } else {
            std::cout << "Unknown command" << std::endl;
        }
    }
    return 0;
}