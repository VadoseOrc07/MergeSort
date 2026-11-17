#include "MergeSort.h"

#include <cstddef>
#include <iostream>
#include <iterator>

template <typename T>
void printArray(const T* data, std::size_t size) {
    for (std::size_t i = 0; i < size; ++i) {
        std::cout << data[i] << ' ';
    }

    std::cout << '\n';
}

int main() {
    int intNumbers[] = {8, -3, 5, 0, 8, -10, 2};

    double doubleNumbers[] = {
        3.5, -2.25, 0.0, 8.75, 3.5, -0.5
    };

    MergeSort<int> intSorter;
    MergeSort<double> doubleSorter;

    std::cout << "int przed:  ";
    printArray(intNumbers, std::size(intNumbers));

    intSorter.sort(intNumbers, std::size(intNumbers));

    std::cout << "int po:     ";
    printArray(intNumbers, std::size(intNumbers));

    std::cout << "double przed: ";
    printArray(doubleNumbers, std::size(doubleNumbers));

    doubleSorter.sort(doubleNumbers, std::size(doubleNumbers));

    std::cout << "double po:    ";
    printArray(doubleNumbers, std::size(doubleNumbers));

    return 0;
}