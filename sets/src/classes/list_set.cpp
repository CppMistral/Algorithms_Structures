#include "list_set.hpp"

#include <iostream>

template <> ListSet fromString<ListSet>(const std::string &s) {
    std::cout << "fromString<ListSet> called\n";
    ListSet set{};
    for (char c : s) {
        if (!set.contains(c)) {
            set.insert(c);
        }
    }
    return set;
}

template <> std::string toString<ListSet>(const ListSet &set) {
    std::cout << "toString<ListSet> called\n";
    std::string result;
    for (char c : UNIVERSE) {
        for (ListSet::ListNode *current = set.head; current != nullptr; current = current->next) {
            if (current->data == c) {
                result += c;
                break;
            }
        }
    }
    return result;
}

ListSet::ListSet(const ListSet &other) {
    std::cout << "ListSet::ListSet copy called\n";
    *this = other;
}

ListSet &ListSet::operator=(const ListSet &other) {
    std::cout << "ListSet::operator= copy called\n";
    if (this != &other) {
        clear();
        copyFrom(other);
    }
    return *this;
}

ListSet::ListSet(ListSet &&other) noexcept : head(other.head), size(other.size) {
    std::cout << "ListSet::ListSet move called\n";
    other.head = nullptr;
    other.size = 0;
}

ListSet &ListSet::operator=(ListSet &&other) noexcept {
    std::cout << "ListSet::operator= move called\n";
    if (this != &other) {
        clear();
        head = other.head;
        size = other.size;
        other.head = nullptr;
        other.size = 0;
    }
    return *this;
}

ListSet::~ListSet() {
    std::cout << "ListSet::~ListSet called\n";
    clear();
}

void ListSet::clear() {
    std::cout << "ListSet::clear called\n";
    ListNode *current = head;
    while (current != nullptr) {
        ListNode *next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
    size = 0;
}

void ListSet::copyFrom(const ListSet &other) {
    std::cout << "ListSet::copyFrom called\n";
    ListNode **tail = &head;
    for (ListNode *current = other.head; current != nullptr; current = current->next) {
        *tail = new ListNode{current->data, nullptr};
        tail = &((*tail)->next);
        ++size;
    }
}

bool ListSet::contains(char c) const {
    std::cout << "ListSet::contains called\n";
    for (ListNode *current = head; current != nullptr; current = current->next) {
        if (current->data == c) {
            return true;
        }
    }
    return false;
}

void ListSet::insert(char c) {
    std::cout << "ListSet::insert called\n";
    ListNode *node = new ListNode{c, head};
    head = node;
    ++size;
}

ListSet ListSet::operator&(const ListSet &other) const {
    std::cout << "ListSet::operator& called\n";
    ListSet result{};
    for (ListNode *current = head; current != nullptr; current = current->next) {
        if (other.contains(current->data)) {
            result.insert(current->data);
        }
    }
    return result;
}

ListSet ListSet::operator|(const ListSet &other) const {
    std::cout << "ListSet::operator| called\n";
    ListSet result{};
    for (ListNode *current = head; current != nullptr; current = current->next) {
        if (!result.contains(current->data)) {
            result.insert(current->data);
        }
    }
    for (ListNode *current = other.head; current != nullptr; current = current->next) {
        if (!result.contains(current->data)) {
            result.insert(current->data);
        }
    }
    return result;
}
