#include "array_set.hpp"

#include <cstdlib>
#include <iostream>

template <> ArraySet fromString<ArraySet>(const std::string &s) {
  std::cout << "fromString<ArraySet> called\n";
  ArraySet set{};
  for (char c : s) {
    if (!set.contains(c)) {
      set.insert(c);
    }
  }
  return set;
}

template <> std::string toString<ArraySet>(const ArraySet &set) {
  std::cout << "toString<ArraySet> called\n";
  std::string result;
  for (char c : UNIVERSE) {
    for (int i = 0; i < set.size; ++i) {
      if (set.elements[i] == c) {
        result += c;
        break;
      }
    }
  }
  return result;
}

bool ArraySet::contains(char c) const {
  std::cout << "ArraySet::contains called\n";
  for (int i = 0; i < size; ++i) {
    if (elements[i] == c) {
      return true;
    }
  }
  return false;
}

void ArraySet::insert(char c) {
  std::cout << "ArraySet::insert called\n";
  elements[size] = c;
  ++size;
  elements[size] = '\0';
}

ArraySet ArraySet::operator&(const ArraySet &other) const {
  std::cout << "ArraySet::operator& called\n";
  ArraySet result{};
  for (int i = 0; i < size; ++i) {
    if (other.contains(elements[i])) {
      result.insert(elements[i]);
    }
  }
  return result;
}

ArraySet ArraySet::operator|(const ArraySet &other) const {
  std::cout << "ArraySet::operator| called\n";
  ArraySet result{};
  for (int i = 0; i < size; ++i) {
    if (!result.contains(elements[i])) {
      result.insert(elements[i]);
    }
  }
  for (int i = 0; i < other.size; ++i) {
    if (!result.contains(other.elements[i])) {
      result.insert(other.elements[i]);
    }
  }
  return result;
}
