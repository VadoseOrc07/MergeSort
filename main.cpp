#include "MergeSort.h"

#include <iostream>
#include <iterator>

int main() {
    int numbers[] = {8, -3, 5, 0, 8, -10, 2};

    MergeSort<int> sorter;
    sorter.sort(numbers, std::size(numbers));

    for (int value : numbers) {
        std::cout << value << ' ';
    }

    std::cout << '\n';

    return 0;
}