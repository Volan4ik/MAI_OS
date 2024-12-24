#include <iostream>
#include <dlfcn.h>

typedef float (*DerivativeFunc)(float, float);
typedef float (*EFunc)(int);

int main() {
    void* handle_derivative = dlopen("./libderivative_first.so", RTLD_LAZY);
    void* handle_e_formule = dlopen("./libe_formule.so", RTLD_LAZY);

    if (!handle_derivative || !handle_e_formule) {
        std::cerr << "Cannot open libraries: " << dlerror() << std::endl;
        return 1;
    }

    DerivativeFunc Derivative = (DerivativeFunc)dlsym(handle_derivative, "Derivative");
    EFunc E = (EFunc)dlsym(handle_e_formule, "E");

    if (!Derivative || !E) {
        std::cerr << "Cannot load symbols: " << dlerror() << std::endl;
        dlclose(handle_derivative);
        dlclose(handle_e_formule);
        return 1;
    }

    int command;
    while (true) {
        std::cout << "Enter command (1 for Derivative, 2 for E, 0 to switch, -1 to exit): ";
        std::cin >> command;

        if (command == -1) {
            break;
        } else if (command == 0) {
            // Переключение реализаций
            dlclose(handle_derivative);
            dlclose(handle_e_formule);

            handle_derivative = dlopen("./libderivative_second.so", RTLD_LAZY);
            handle_e_formule = dlopen("./libe_series.so", RTLD_LAZY);

            if (!handle_derivative || !handle_e_formule) {
                std::cerr << "Cannot open libraries: " << dlerror() << std::endl;
                return 1;
            }

            Derivative = (DerivativeFunc)dlsym(handle_derivative, "Derivative");
            E = (EFunc)dlsym(handle_e_formule, "E");

            if (!Derivative || !E) {
                std::cerr << "Cannot load symbols: " << dlerror() << std::endl;
                dlclose(handle_derivative);
                dlclose(handle_e_formule);
                return 1;
            }

            std::cout << "Switched to derivative_second and e_series libraries" << std::endl;
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

    dlclose(handle_derivative);
    dlclose(handle_e_formule);
    return 0;
}