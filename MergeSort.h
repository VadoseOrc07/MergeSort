#ifndef MERGE_SORT_H
#define MERGE_SORT_H

#include <cstddef>
#include <stdexcept>
#include <vector>

/**
 * @brief Sortowanie tablic rosnaco algorytmem MergeSort.
 * @tparam T Typ elementow tablicy, np. int, long int, double, float.
 *
 * Zlozonosc czasowa: O(n log n).
 * Dodatkowa pamiec: O(n).
 */

template <typename T>
class MergeSort {
public:
    /**
 * @brief Sortuje przekazana tablice.
 * @param data Wskaznik do pierwszego elementu.
 * @param size Liczba elementow tablicy.
 * @throws std::invalid_argument Gdy data jest nullptr i size > 0.
 */
    void sort(T* data, std::size_t size) const {
        if (size == 0) {
            return;
        }

        if (data == nullptr) {
            throw std::invalid_argument(
                "Brak tablicy dla niezerowego rozmiaru"
            );
        }

        if (size == 1) {
            return;
        }

        std::vector<T> buffer(data, data + size);

        sortRange(data, buffer.data(), 0, size);
    }

private:
    /**
 * @brief Rekurencyjnie sortuje przedzial [left, right).
 */
    void sortRange(
        T* data,
        T* buffer,
        std::size_t left,
        std::size_t right
    ) const {
        if (right - left < 2) {
            return;
        }

        const std::size_t middle = left + (right - left) / 2;

        sortRange(data, buffer, left, middle);
        sortRange(data, buffer, middle, right);

        merge(data, buffer, left, middle, right);
    }
    /**
 * @brief Scala dwie posortowane czesci tablicy przez bufor pomocniczy.
 */
    void merge(
        T* data,
        T* buffer,
        std::size_t left,
        std::size_t middle,
        std::size_t right
    ) const {
        std::size_t i = left;
        std::size_t j = middle;
        std::size_t k = left;

        while (i < middle && j < right) {
            if (data[j] < data[i]) {
                buffer[k++] = data[j++];
            } else {
                buffer[k++] = data[i++];
            }
        }

        while (i < middle) {
            buffer[k++] = data[i++];
        }

        while (j < right) {
            buffer[k++] = data[j++];
        }

        for (std::size_t index = left; index < right; ++index) {
            data[index] = buffer[index];
        }
    }
};

#endif