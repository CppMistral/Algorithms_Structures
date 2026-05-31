#pragma once

#include "../common.hpp"

struct ListNode {
  char data;
  ListNode *next;
};

struct ListSet {
  ListSet() = default;
  ~ListSet();

  ListNode *head = nullptr;
  int size = 0;
};

template <> ListSet fromString<ListSet>(const std::string &s);
template <> std::string toString<ListSet>(const ListSet &set);

bool contains(const ListSet &set, char c);
void insert(ListSet &set, char c);

ListSet operator&(const ListSet &a, const ListSet &b);
ListSet operator|(const ListSet &a, const ListSet &b);
