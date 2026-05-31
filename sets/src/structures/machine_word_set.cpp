#include "machine_word_set.hpp"

constexpr inline uint16_t universeMask =
    static_cast<uint16_t>((1u << UNIVERSE_SIZE) - 1u);

template <> MachineWordSet fromString<MachineWordSet>(const std::string &s) {
  MachineWordSet set{};
  for (char c : s) {
    insert(set, c);
  }
  return set;
}

void insert(MachineWordSet &set, char c) {
  const int index = charToIndex(c);
  set.bits = static_cast<uint16_t>(set.bits | (1u << index));
}

template <> std::string toString<MachineWordSet>(const MachineWordSet &set) {
  std::string result;
  for (int i = 0; i < UNIVERSE_SIZE; ++i) {
    if ((set.bits & (1u << i)) != 0) {
      result += indexToChar(i);
    }
  }
  return result;
}

MachineWordSet operator&(const MachineWordSet &a, const MachineWordSet &b) {
  return {static_cast<uint16_t>(a.bits & b.bits & universeMask)};
}

MachineWordSet operator|(const MachineWordSet &a, const MachineWordSet &b) {
  return {static_cast<uint16_t>((a.bits | b.bits) & universeMask)};
}
