#include "list_set.hpp"

template <> ListSet fromString<ListSet>(const std::string &s) {
  ListSet set{};
  for (char c : s) {
    if (!contains(set, c)) {
      insert(set, c);
    }
  }
  return set;
}

ListSet::~ListSet() {
  ListNode *current = head;
  while (current != nullptr) {
    ListNode *next = current->next;
    delete current;
    current = next;
  }
  head = nullptr;
  size = 0;
}

bool contains(const ListSet &set, char c) {
  for (ListNode *current = set.head; current != nullptr;
       current = current->next) {
    if (current->data == c) {
      return true;
    }
  }
  return false;
}

void insert(ListSet &set, char c) {
  ListNode *node = new ListNode{c, set.head};
  set.head = node;
  ++set.size;
}

template <> std::string toString<ListSet>(const ListSet &set) {
  std::string result;
  for (char c : UNIVERSE) {
    for (ListNode *current = set.head; current != nullptr;
         current = current->next) {
      if (current->data == c) {
        result += c;
        break;
      }
    }
  }
  return result;
}

ListSet operator&(const ListSet &a, const ListSet &b) {
  ListSet result{};
  for (ListNode *current = a.head; current != nullptr;
       current = current->next) {
    if (contains(b, current->data)) {
      insert(result, current->data);
    }
  }
  return result;
}

ListSet operator|(const ListSet &a, const ListSet &b) {
  ListSet result{};
  for (ListNode *current = a.head; current != nullptr;
       current = current->next) {
    if (!contains(result, current->data)) {
      insert(result, current->data);
    }
  }
  for (ListNode *current = b.head; current != nullptr;
       current = current->next) {
    if (!contains(result, current->data)) {
      insert(result, current->data);
    }
  }
  return result;
}
