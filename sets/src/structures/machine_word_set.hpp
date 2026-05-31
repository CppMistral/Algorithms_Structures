#pragma once

#include "../common.hpp"

struct MachineWordSet {
  uint16_t bits = 0;
};

template <> MachineWordSet fromString<MachineWordSet>(const std::string &s);
template <> std::string toString<MachineWordSet>(const MachineWordSet &set);

void insert(MachineWordSet &set, char c);

MachineWordSet operator&(const MachineWordSet &a, const MachineWordSet &b);
MachineWordSet operator|(const MachineWordSet &a, const MachineWordSet &b);
