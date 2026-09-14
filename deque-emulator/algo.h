#pragma once

#include <deque>

template<typename T, typename Compare>
std::deque<T> Merge(const std::deque<T>& left, const std::deque<T>& right, const Compare& comp) {
    std::deque<T> result;
    size_t i = 0, j = 0;

    while (i < left.size() && j < right.size()) {
        if (comp(left[i], right[j])) {
            result.push_back(left[i]);
            ++i;
        } else {
            result.push_back(right[j]);
            ++j;
        }
    }

    while (i < left.size()) {
        result.push_back(left[i]);
        ++i;
    }

    while (j < right.size()) {
        result.push_back(right[j]);
        ++j;
    }

    return result;
}

template<typename T, typename Compare>
std::deque<T> MergeSort(const std::deque<T>& container, const Compare& comp) {
    if (container.size() <= 1) {
        return container;
    }

    size_t mid = container.size() / 2;
    std::deque<T> left;
    std::deque<T> right;

    for (size_t i = 0; i < mid; ++i) {
        left.push_back(container[i]);
    }
    for (size_t i = mid; i < container.size(); ++i) {
        right.push_back(container[i]);
    }

    left = MergeSort(left, comp);
    right = MergeSort(right, comp);

    return Merge(left, right, comp);
}
