#include "array_set.hpp"

template <> ArraySet fromString<ArraySet>(const std::string &s) {
  ArraySet set{};
  for (char c : s) {
    if (!contains(set, c)) {
      insert(set, c);
    }
  }
  return set;
}

bool contains(const ArraySet &set, char c) {
  for (int i = 0; i < set.size; ++i) {
    if (set.elements[i] == c) {
      return true;
    }
  }
  return false;
}

void insert(ArraySet &set, char c) {
  set.elements[set.size] = c;
  ++set.size;
  set.elements[set.size] = '\0';
}

template <> std::string toString<ArraySet>(const ArraySet &set) {
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

ArraySet operator&(const ArraySet &a, const ArraySet &b) {
  ArraySet result{};
  for (int i = 0; i < a.size; ++i) {
    if (contains(b, a.elements[i])) {
      insert(result, a.elements[i]);
    }
  }
  return result;
}

ArraySet operator|(const ArraySet &a, const ArraySet &b) {
  ArraySet result{};
  for (int i = 0; i < a.size; ++i) {
    if (!contains(result, a.elements[i])) {
      insert(result, a.elements[i]);
    }
  }
  for (int i = 0; i < b.size; ++i) {
    if (!contains(result, b.elements[i])) {
      insert(result, b.elements[i]);
    }
  }
  return result;
}
