#ifndef MERGE_SORT_H
#define MERGE_SORT_H

#include <cstddef>
#include <stdexcept>
#include <vector>

template <typename T>
class MergeSort {
public:
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