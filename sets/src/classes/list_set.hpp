#pragma once

#include "../common.hpp"

class ListSet {
public:
  ListSet() = default;
  ListSet(const ListSet &other);
  ListSet &operator=(const ListSet &other);
  ListSet(ListSet &&other) noexcept;
  ListSet &operator=(ListSet &&other) noexcept;
  ~ListSet();

  bool contains(char c) const;
  void insert(char c);

  ListSet operator&(const ListSet &other) const;
  ListSet operator|(const ListSet &other) const;

private:
  friend std::string toString<ListSet>(const ListSet &set);

  struct ListNode {
    char data;
    ListNode *next;
  };

  void clear();
  void copyFrom(const ListSet &other);

  ListNode *head = nullptr;
  int size = 0;
};

template <> ListSet fromString<ListSet>(const std::string &s);
template <> std::string toString<ListSet>(const ListSet &set);
