#include "graph_generator.hpp"

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <string>

namespace {

void printHelp() {
    std::cout << "Использование:\n"
              << "  ./graph [количество_вершин] [количество_тестов]\n"
              << "  ./graph --help\n";
}

std::size_t parseSize(const char *value, const char *name) {
    try {
        std::size_t parsedCharacters = 0;
        const std::string text(value);
        const unsigned long long parsedValue = std::stoull(text, &parsedCharacters);
        if (parsedCharacters != text.size()) {
            throw std::invalid_argument("extra characters");
        }

        return static_cast<std::size_t>(parsedValue);
    } catch (const std::exception &) {
        std::cerr << "Некорректное значение аргумента " << name << ": " << value << '\n';
        std::exit(1);
    }
}

} // namespace

int main(int argc, char *argv[]) {
    if (argc > 1 && (std::string(argv[1]) == "--help" || std::string(argv[1]) == "-h")) {
        printHelp();
        return 0;
    }

    if (argc > 3) {
        printHelp();
        return 1;
    }

    const std::size_t vertexCount = argc > 1 ? parseSize(argv[1], "количество_вершин") : 15;
    const std::size_t testCount = argc > 2 ? parseSize(argv[2], "количество_тестов") : 5;

    GraphGenerator generator;

    std::cout << "Вариант 31: построение глубинного стягивающего леса "
              << "для неориентированного графа.\n\n";

    for (std::size_t test = 1; test <= testCount; ++test) {
        const bool makeConnected = test % 2 == 1;
        const GraphGenerator::GeneratedGraph generated =
            generator.generate(vertexCount, makeConnected);

        std::cout << "--- Тест " << test << " ---\n";
        std::cout << "Тип графа: " << (makeConnected ? "связный" : "произвольный") << '\n';
        std::cout << "Вершин: " << generated.graph.vertexCount()
                  << ", ребер: " << generated.edgeCount << '\n';
        generated.graph.print(std::cout);

        const auto start = std::chrono::high_resolution_clock::now();
        const Graph::SpanningForest forest = generated.graph.spanningForest();
        const auto end = std::chrono::high_resolution_clock::now();

        forest.printResult(std::cout);

        const auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << "Граф " << (forest.isGraphConnected() ? "связный" : "несвязный") << '\n';
        std::cout << "Время построения: " << duration.count() << " мкс\n\n";
    }

    return 0;
}
