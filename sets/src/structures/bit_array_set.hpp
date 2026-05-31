#pragma once

#include "../common.hpp"

struct BitArraySet {
  std::array<bool, UNIVERSE_SIZE> bits{};
};

template <> BitArraySet fromString<BitArraySet>(const std::string &s);
template <> std::string toString<BitArraySet>(const BitArraySet &set);

void insert(BitArraySet &set, char c);

BitArraySet operator&(const BitArraySet &a, const BitArraySet &b);
BitArraySet operator|(const BitArraySet &a, const BitArraySet &b);
