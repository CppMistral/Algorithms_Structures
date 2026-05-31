#pragma once

#include "../common.hpp"

class BitArraySet {
public:
  BitArraySet() = default;
  explicit BitArraySet(char);
  BitArraySet(const BitArraySet &other) = default;
  BitArraySet &operator=(const BitArraySet &other) = default;
  BitArraySet(BitArraySet &&other) noexcept = default;
  BitArraySet &operator=(BitArraySet &&other) noexcept = default;
  ~BitArraySet() = default;

  void insert(char c);

  BitArraySet operator&(const BitArraySet &other) const;
  BitArraySet operator|(const BitArraySet &other) const;

private:
  friend std::string toString<BitArraySet>(const BitArraySet &set);

  std::array<bool, UNIVERSE_SIZE> bits{};
};

template <> BitArraySet fromString<BitArraySet>(const std::string &s);
template <> std::string toString<BitArraySet>(const BitArraySet &set);
