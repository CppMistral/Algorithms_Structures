#pragma once

#include "../common.hpp"

struct BitArraySet {
    bool bits[UNIVERSE_SIZE]{};
};

template <> BitArraySet fromString<BitArraySet>(const std::string &s);
template <> std::string toString<BitArraySet>(const BitArraySet &set);

void insert(BitArraySet &set, char c);

BitArraySet operator&(const BitArraySet &a, const BitArraySet &b);
BitArraySet operator|(const BitArraySet &a, const BitArraySet &b);
