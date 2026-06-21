#include "list_set.hpp"

template <> ListSet fromString<ListSet>(const std::string &s) {
    ListSet set{};
    for (char c : s) {
        if (!set.contains(c)) {
            set.insert(c);
        }
    }
    return set;
}

template <> std::string toString<ListSet>(const ListSet &set) {
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
    *this = other;
}

ListSet &ListSet::operator=(const ListSet &other) {
    if (this != &other) {
        clear();
        copyFrom(other);
    }
    return *this;
}

ListSet::ListSet(ListSet &&other) noexcept : head(other.head), size(other.size) {
    other.head = nullptr;
    other.size = 0;
}

ListSet &ListSet::operator=(ListSet &&other) noexcept {
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
    clear();
}

void ListSet::clear() {
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
    ListNode **tail = &head;
    for (ListNode *current = other.head; current != nullptr; current = current->next) {
        *tail = new ListNode{current->data, nullptr};
        tail = &((*tail)->next);
        ++size;
    }
}

bool ListSet::contains(char c) const {
    for (ListNode *current = head; current != nullptr; current = current->next) {
        if (current->data == c) {
            return true;
        }
    }
    return false;
}

void ListSet::insert(char c) {
    ListNode *node = new ListNode{c, head};
    head = node;
    ++size;
}

ListSet ListSet::operator&(const ListSet &other) const {
    ListSet result{};
    for (ListNode *current = head; current != nullptr; current = current->next) {
        if (other.contains(current->data)) {
            result.insert(current->data);
        }
    }
    return result;
}

ListSet ListSet::operator|(const ListSet &other) const {
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
