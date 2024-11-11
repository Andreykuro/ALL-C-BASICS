//
// Created by Acer on 11/11/2024.
//

#include "SFINAE.h"
#include <iostream>
#include <type_traits>

template<typename T>
typename std::enable_if<std::is_integral<T>::value, void>::type print(T value) {
    std::cout << "Integral type: " << value << std::endl;
}

template<typename T>
typename std::enable_if<!std::is_integral<T>::value, void>::type print(T value) {
    std::cout << "Non-integral type: " << value << std::endl;
}

int main() {
    print(42);          // Integral type
    print(3.14);        // Non-integral type
    return 0;
}
