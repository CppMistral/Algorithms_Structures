#include "graph.hpp"
#include "graph_generator.hpp"

#include <iostream>
#include <sstream>
#include <string>

namespace {

void printHelp() {
    std::cout << "Использование:\n"
              << "  ./graph [-c / --connected | -d / --disconnected]\n"
              << "  ./graph --example\n"
              << "  ./graph --help\n";
}

int runExample() {
    Graph graph(7);
    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(1, 3);
    graph.addEdge(4, 5);

    std::cout << "Вершин: " << graph.vertexCount() << '\n';
    graph.print();
    std::cout << '\n';

    const std::string expected = "Глубинный стягивающий лес\n"
                                 "Дерево 1: (0, 1) (0, 2) (1, 3)\n"
                                 "Дерево 2: (4, 5)\n"
                                 "Дерево 3: 6\n";

    std::ostringstream actualStream;
    graph.spanningForest().print(actualStream);
    const std::string actual = actualStream.str();

    std::cout << "Ожидаемый результат:\n"
              << expected << "Фактический результат:\n"
              << actual << "Сравнение: " << (expected == actual ? "совпадает" : "не совпадает")
              << '\n';

    return 0;
}

} // namespace

int main(int argc, char *argv[]) {
    if (argc == 1) {
        printHelp();
        return 0;
    }
    if (argc > 1 && (std::string(argv[1]) == "--help" || std::string(argv[1]) == "-h")) {
        printHelp();
        return 0;
    }

    if (argc > 2) {
        printHelp();
        return 1;
    }

    bool connected = true;
    if (argc == 2) {
        const std::string mode(argv[1]);
        if (mode == "--connected" || mode == "-c") {
            connected = true;
        } else if (mode == "--disconnected" || mode == "-d") {
            connected = false;
        } else if (mode == "--example") {
            return runExample();
        } else {
            printHelp();
            return 1;
        }
    }

    GraphGenerator generator;
    const Graph graph = generator.generateRandom(connected);
    std::cout << "Режим генерации: " << (connected ? "связный граф" : "несвязный граф") << "\n\n";
    std::cout << "Вершин: " << graph.vertexCount() << '\n';
    graph.print();
    std::cout << '\n';

    const Graph::SpanningForest forest = graph.spanningForest();
    forest.print();
    std::cout << "Граф " << (forest.isGraphConnected() ? "связный" : "несвязный") << '\n';

    return 0;
}
