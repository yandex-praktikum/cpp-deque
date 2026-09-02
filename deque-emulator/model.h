#pragma once

#include <deque>
#include <string>
#include <random>

struct Model {
    using container = std::deque<std::string>;
    container items;
    container::iterator iterator = items.begin();

    std::mt19937 random_gen;
};
