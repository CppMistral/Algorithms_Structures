#include "bit_array_set.hpp"

#include <cstdlib>
#include <iostream>

template <> BitArraySet fromString<BitArraySet>(const std::string &s) {
    std::cout << "fromString<BitArraySet> called\n";
    BitArraySet set{};
    for (char c : s) {
        set.insert(c);
    }
    return set;
}

void BitArraySet::insert(char c) {
    std::cout << "BitArraySet::insert called\n";
    const int index = charToIndex(c);
    bits[index] = true;
}

template <> std::string toString<BitArraySet>(const BitArraySet &set) {
    std::cout << "toString<BitArraySet> called\n";
    std::string result;
    for (int i = 0; i < UNIVERSE_SIZE; ++i) {
        if (set.bits[i]) {
            result += indexToChar(i);
        }
    }
    return result;
}

BitArraySet BitArraySet::operator&(const BitArraySet &other) const {
    std::cout << "BitArraySet::operator& called\n";
    BitArraySet result{};
    for (int i = 0; i < UNIVERSE_SIZE; ++i) {
        result.bits[i] = bits[i] && other.bits[i];
    }
    return result;
}

BitArraySet BitArraySet::operator|(const BitArraySet &other) const {
    std::cout << "BitArraySet::operator| called\n";
    BitArraySet result{};
    for (int i = 0; i < UNIVERSE_SIZE; ++i) {
        result.bits[i] = bits[i] || other.bits[i];
    }
    return result;
}
