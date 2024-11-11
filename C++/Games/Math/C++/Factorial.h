//
// Created by Acer on 11/11/2024.
//

#ifndef FACTORIAL_H
#define FACTORIAL_H

namespace Andrey {
#include <iostream>

    template<int N>
    struct Factorial {
        static constexpr int value = N * Factorial<N - 1>::value;
    };

    template<>
    struct Factorial<0> {
        static constexpr int value = 1;
    };

    int main() {
        std::cout << "Factorial of 5 is: " << Factorial<5>::value << std::endl;  // Output: 120
        return 0;
    }

} // Andrey

#endif //FACTORIAL_H
