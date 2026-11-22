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
// 6. Pusta tablica bez wyjatku.
TYPED_TEST(MergeSortTest, EmptyArray) {
    std::vector<TypeParam> data;

    EXPECT_NO_THROW(
        this->sorter.sort(data.data(), data.size())
    );

    EXPECT_TRUE(data.empty());

    EXPECT_NO_THROW(
        this->sorter.sort(nullptr, 0)
    );
}

// 7. Jeden element pozostaje bez zmian.
TYPED_TEST(MergeSortTest, SingleElement) {
    std::vector<TypeParam> data = {42};
    const auto expected = data;

    this->sorter.sort(data.data(), data.size());

    EXPECT_EQ(data, expected);
}

// 8. Dodatnie liczby z duplikatami.
TYPED_TEST(MergeSortTest, Duplicates) {
    std::vector<TypeParam> data = {4, 2, 4, 1, 2, 4};

    const std::vector<TypeParam> expected = {
        1, 2, 2, 4, 4, 4
    };

    this->sorter.sort(data.data(), data.size());

    EXPECT_EQ(data, expected);
}

// 9. Ujemne liczby z duplikatami.
TYPED_TEST(MergeSortTest, NegativeDuplicates) {
    std::vector<TypeParam> data = {-3, -1, -3, -8, -1};

    const std::vector<TypeParam> expected = {
        -8, -3, -3, -1, -1
    };

    this->sorter.sort(data.data(), data.size());

    EXPECT_EQ(data, expected);
}

// 10. Oba znaki i duplikaty.
TYPED_TEST(MergeSortTest, MixedSignsAndDuplicates) {
    std::vector<TypeParam> data = {-2, 4, -2, 0, 4, 1, -5};

    const std::vector<TypeParam> expected = {
        -5, -2, -2, 0, 1, 4, 4
    };

    this->sorter.sort(data.data(), data.size());

    EXPECT_EQ(data, expected);
}

// 11. Dwa elementy rosnaco.
TYPED_TEST(MergeSortTest, TwoAscendingElements) {
    std::vector<TypeParam> data = {1, 2};
    const auto expected = data;

    this->sorter.sort(data.data(), data.size());

    EXPECT_EQ(data, expected);
}

// 12. Duza tablica - 1000 elementow.
TYPED_TEST(MergeSortTest, LargeArray) {
    std::mt19937 generator(300);
    std::uniform_int_distribution<int> distribution(0, 10000);

    std::vector<TypeParam> data(1000);

    for (auto& value : data) {
        value = static_cast<TypeParam>(distribution(generator));
    }

    auto expected = data;
    std::sort(expected.begin(), expected.end());

    this->sorter.sort(data.data(), data.size());

    EXPECT_EQ(data, expected);
}

// 13. Duza tablica, oba znaki i duplikaty.
TYPED_TEST(MergeSortTest, LargeMixedArrayWithDuplicates) {
    std::vector<TypeParam> data;

    for (int i = 0; i < 1000; ++i) {
        data.push_back(
            static_cast<TypeParam>((i * 37) % 101 - 50)
        );
    }

    auto expected = data;
    std::sort(expected.begin(), expected.end());

    this->sorter.sort(data.data(), data.size());

    EXPECT_EQ(data, expected);
}

// Dodatkowo: dwa elementy malejaco.
TYPED_TEST(MergeSortTest, TwoDescendingElements) {
    std::vector<TypeParam> data = {2, 1};
    const std::vector<TypeParam> expected = {1, 2};

    this->sorter.sort(data.data(), data.size());

    EXPECT_EQ(data, expected);
}

// Dodatkowo: wszystkie wartosci jednakowe.
TYPED_TEST(MergeSortTest, AllValuesEqual) {
    std::vector<TypeParam> data(
        20,
        static_cast<TypeParam>(7)
    );

    const auto expected = data;

    this->sorter.sort(data.data(), data.size());

    EXPECT_EQ(data, expected);
}

// Dodatkowo: pusty wskaznik przy dodatnim rozmiarze.
TYPED_TEST(MergeSortTest, NullPointerWithNonzeroSize) {
    EXPECT_THROW(
        this->sorter.sort(nullptr, 1),
        std::invalid_argument
    );

    EXPECT_THROW(
        this->sorter.sort(nullptr, 2),
        std::invalid_argument
    );
}

// Osobne testy wartosci ulamkowych.
template <typename T>
class FloatingMergeSortTest : public ::testing::Test {};

using FloatingTypes = ::testing::Types<double, float>;

TYPED_TEST_SUITE(FloatingMergeSortTest, FloatingTypes);

TYPED_TEST(FloatingMergeSortTest, FractionalValues) {
    std::vector<TypeParam> data = {
        3.5, -2.25, 0.0, 8.75, 3.5, -0.5
    };

    const std::vector<TypeParam> expected = {
        -2.25, -0.5, 0.0, 3.5, 3.5, 8.75
    };

    MergeSort<TypeParam> sorter;
    sorter.sort(data.data(), data.size());

    EXPECT_EQ(data, expected);
}