#include "machine_word_set.hpp"

#include <iostream>

constexpr inline uint16_t universeMask = static_cast<uint16_t>((1u << UNIVERSE_SIZE) - 1u);

template <> MachineWordSet fromString<MachineWordSet>(const std::string &s) {
    std::cout << "fromString<MachineWordSet> called\n";
    MachineWordSet set{};
    for (char c : s) {
        set.insert(c);
    }
    return set;
}

void MachineWordSet::insert(char c) {
    std::cout << "MachineWordSet::insert called\n";
    const int index = charToIndex(c);
    bits = static_cast<uint16_t>(bits | (1u << index));
}

template <> std::string toString<MachineWordSet>(const MachineWordSet &set) {
    std::cout << "toString<MachineWordSet> called\n";
    std::string result;
    for (int i = 0; i < UNIVERSE_SIZE; ++i) {
        if ((set.bits & (1u << i)) != 0) {
            result += indexToChar(i);
        }
    }
    return result;
}

MachineWordSet MachineWordSet::operator&(const MachineWordSet &other) const {
    std::cout << "MachineWordSet::operator& called\n";
    MachineWordSet result{};
    result.bits = static_cast<uint16_t>(bits & other.bits & universeMask);
    return result;
}

MachineWordSet MachineWordSet::operator|(const MachineWordSet &other) const {
    std::cout << "MachineWordSet::operator| called\n";
    MachineWordSet result{};
    result.bits = static_cast<uint16_t>((bits | other.bits) & universeMask);
    return result;
}
