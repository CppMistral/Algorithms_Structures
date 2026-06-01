#include "graph_generator.hpp"

#include <iostream>
#include <string>

namespace {

void printHelp() {
    std::cout << "Использование:\n"
              << "  ./graph [-c / --connected | -d / --disconnected]\n"
              << "  ./graph --help\n";
}

} // namespace

int main(int argc, char *argv[]) {
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
