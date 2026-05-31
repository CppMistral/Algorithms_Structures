#include "binary_tree.hpp"

#include <iostream>
#include <string>

void printHelp() {
    std::cout << "Использование:\n"
              << "  ./tree --test     тестовое дерево\n"
              << "  ./tree --manual   ручной ввод структуры дерева\n"
              << "  ./tree --help     справка\n";
}

int main(int argc, char *argv[]) {
    std::string mode = "--help";
    if (argc > 2) {
        printHelp();
        return 1;
    }
    if (argc == 2) {
        mode = argv[1];
    }

    BinaryTree tree;
    if (mode == "--test") {
        tree = BinaryTree::buildTest();
    } else if (mode == "--manual") {
        tree = BinaryTree::buildManual();
    } else if (mode == "--help" || mode == "-h") {
        printHelp();
        return 0;
    } else {
        printHelp();
        return 1;
    }

    std::cout << "Практическая работа по теме 3 \"Деревья\"\n"
              << "Вариант 31: двоичное дерево, симметричная разметка, обход в ширину.\n\n";
    tree.print();

    return 0;
}
