#pragma once

#include <array>
#include <cstdint>
#include <string>

inline constexpr std::array<char, 13> UNIVERSE = {
    '+', '-', '*', '/', '%', '&', '|', '^', '~', '!', '<', '>', '='};

inline constexpr int UNIVERSE_SIZE = static_cast<int>(UNIVERSE.size());
inline constexpr std::string UNIVERSE_STR = "+-*/%&|^~!<>=";

inline constexpr int charToIndex(char c) {
  for (int i = 0; i < UNIVERSE_SIZE; ++i) {
    if (UNIVERSE[i] == c) {
      return i;
    }
  }
  return -1;
}

inline constexpr char indexToChar(int i) {
  if (i < 0 || i >= UNIVERSE_SIZE) {
    return '\0';
  }
  return UNIVERSE[i];
}

inline constexpr bool isValidChar(char c) { return charToIndex(c) != -1; }

template <typename Set>
inline Set solve(const Set &a, const Set &b, const Set &c, const Set &d) {
  return d | (a & b & c);
}

template <typename Set> Set fromString(const std::string &s);
template <typename Set> std::string toString(const Set &set);
