#pragma once

#include "../common.hpp"

class ArraySet {
  public:
    ArraySet() = default;
    ArraySet(const ArraySet &other) = default;
    ArraySet &operator=(const ArraySet &other) = default;
    ArraySet(ArraySet &&other) noexcept = default;
    ArraySet &operator=(ArraySet &&other) noexcept = default;
    ~ArraySet() = default;

    bool contains(char c) const;
    void insert(char c);

    ArraySet operator&(const ArraySet &other) const;
    ArraySet operator|(const ArraySet &other) const;

  private:
    friend std::string toString<ArraySet>(const ArraySet &set);

    char elements[UNIVERSE_SIZE + 1]{};
    int size = 0;
};

template <> ArraySet fromString<ArraySet>(const std::string &s);
