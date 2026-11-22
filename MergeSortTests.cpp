#include "MergeSort.h"

#include <gtest/gtest.h>

#include <algorithm>
#include <random>
#include <stdexcept>
#include <vector>

template <typename T>
class MergeSortTest : public ::testing::Test {
protected:
    MergeSort<T> sorter;
};

using NumberTypes = ::testing::Types<
    int,
    long int,
    double,
    float
>;

TYPED_TEST_SUITE(MergeSortTest, NumberTypes);

// 1. Tablica juz posortowana.
TYPED_TEST(MergeSortTest, AlreadySorted) {
    std::vector<TypeParam> data = {1, 2, 3, 4, 5};
    const auto expected = data;

    this->sorter.sort(data.data(), data.size());

    EXPECT_EQ(data, expected);
}

// 2. Odwrotna kolejnosc.
TYPED_TEST(MergeSortTest, ReverseOrder) {
    std::vector<TypeParam> data = {5, 4, 3, 2, 1};
    const std::vector<TypeParam> expected = {1, 2, 3, 4, 5};

    this->sorter.sort(data.data(), data.size());

    EXPECT_EQ(data, expected);
}

// 3. Dane pseudolosowe.
TYPED_TEST(MergeSortTest, RandomValues) {
    std::mt19937 generator(2026);
    std::uniform_int_distribution<int> distribution(0, 500);

    std::vector<TypeParam> data(64);

    for (auto& value : data) {
        value = static_cast<TypeParam>(distribution(generator));
    }

    auto expected = data;
    std::sort(expected.begin(), expected.end());

    this->sorter.sort(data.data(), data.size());

    EXPECT_EQ(data, expected);
}

// 4. Tylko liczby ujemne.
TYPED_TEST(MergeSortTest, NegativeValues) {
    std::vector<TypeParam> data = {-1, -8, -3, -12, -6};

    const std::vector<TypeParam> expected = {
        -12, -8, -6, -3, -1
    };

    this->sorter.sort(data.data(), data.size());

    EXPECT_EQ(data, expected);
}

// 5. Liczby ujemne, dodatnie i zero.
TYPED_TEST(MergeSortTest, MixedSigns) {
    std::vector<TypeParam> data = {-4, 7, 0, -1, 3, -9};

    const std::vector<TypeParam> expected = {
        -9, -4, -1, 0, 3, 7
    };

    this->sorter.sort(data.data(), data.size());

    EXPECT_EQ(data, expected);
}