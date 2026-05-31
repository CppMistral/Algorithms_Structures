#include "binary_tree.hpp"

#include <iostream>
#include <string>

void printHelp() {
    std::cout << "Использование:\n"
              << "  ./tree --sample   готовое дерево для демонстрации\n"
              << "  ./tree --manual   ручной ввод структуры дерева\n"
              << "  ./tree --random   случайное дерево\n"
              << "  ./tree --help     справка\n";
}

int main(int argc, char *argv[]) {
    std::string mode = "--sample";
    if (argc > 2) {
        printHelp();
        return 1;
    }
    if (argc == 2) {
        mode = argv[1];
    }

    BinaryTree tree;
    if (mode == "--sample") {
        tree = BinaryTree::buildSample();
    } else if (mode == "--manual") {
        tree = BinaryTree::buildManual();
    } else if (mode == "--random") {
        tree = BinaryTree::buildRandom();
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
    if (tree.empty()) {
        return 0;
    }

    std::cout << '\n';
    tree.printBreadthFirst();
    tree.printDescendants();

    return 0;
}
