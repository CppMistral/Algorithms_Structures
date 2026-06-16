#pragma once

#include "../common.hpp"

struct ArraySet {
    char elements[UNIVERSE_SIZE + 1]{};
    int size = 0;
};

template <> ArraySet fromString<ArraySet>(const std::string &s);
template <> std::string toString<ArraySet>(const ArraySet &set);

bool contains(const ArraySet &set, char c);
void insert(ArraySet &set, char c);

ArraySet operator&(const ArraySet &a, const ArraySet &b);
ArraySet operator|(const ArraySet &a, const ArraySet &b);
