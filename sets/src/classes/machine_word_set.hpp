#pragma once

#include "../common.hpp"

class MachineWordSet {
public:
  MachineWordSet() = default;
  explicit MachineWordSet(char);
  MachineWordSet(const MachineWordSet &other) = default;
  MachineWordSet &operator=(const MachineWordSet &other) = default;
  MachineWordSet(MachineWordSet &&other) noexcept = default;
  MachineWordSet &operator=(MachineWordSet &&other) noexcept = default;
  ~MachineWordSet() = default;

  void insert(char c);

  MachineWordSet operator&(const MachineWordSet &other) const;
  MachineWordSet operator|(const MachineWordSet &other) const;

private:
  friend std::string toString<MachineWordSet>(const MachineWordSet &set);

  uint16_t bits = 0;
};

template <> MachineWordSet fromString<MachineWordSet>(const std::string &s);
template <> std::string toString<MachineWordSet>(const MachineWordSet &set);
