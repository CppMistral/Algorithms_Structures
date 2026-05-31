#include "bit_array_set.hpp"

template <> BitArraySet fromString<BitArraySet>(const std::string &s) {
  BitArraySet set{};
  for (char c : s) {
    insert(set, c);
  }
  return set;
}

void insert(BitArraySet &set, char c) {
  const int index = charToIndex(c);
  set.bits[index] = true;
}

template <> std::string toString<BitArraySet>(const BitArraySet &set) {
  std::string result;
  for (int i = 0; i < UNIVERSE_SIZE; ++i) {
    if (set.bits[i]) {
      result += indexToChar(i);
    }
  }
  return result;
}

BitArraySet operator&(const BitArraySet &a, const BitArraySet &b) {
  BitArraySet result{};
  for (int i = 0; i < UNIVERSE_SIZE; ++i) {
    result.bits[i] = a.bits[i] && b.bits[i];
  }
  return result;
}

BitArraySet operator|(const BitArraySet &a, const BitArraySet &b) {
  BitArraySet result{};
  for (int i = 0; i < UNIVERSE_SIZE; ++i) {
    result.bits[i] = a.bits[i] || b.bits[i];
  }
  return result;
}
