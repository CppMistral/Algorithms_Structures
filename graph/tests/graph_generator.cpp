#include "graph_generator.hpp"

#include <cstdlib>
#include <ctime>

GraphGenerator::GraphGenerator() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
}

Graph GraphGenerator::generateRandom(bool connected) {
    const std::size_t vertexCount =
        connected ? randomSize(MaxVertexCount - 1) + 1 : randomSize(MaxVertexCount - 2) + 2;
    Graph graph(vertexCount);

    if (connected) {
        generateConnected(graph);
    } else {
        generateDisconnected(graph);
    }

    return graph;
}

void GraphGenerator::generateConnected(Graph &graph) {
    for (Graph::Vertex vertex = 1; vertex < graph.vertexCount(); ++vertex) {
        graph.addEdge(vertex, randomSize(vertex - 1));
    }

    addRandomEdges(graph, 0, graph.vertexCount());
}

void GraphGenerator::generateDisconnected(Graph &graph) {
    if (graph.vertexCount() < 2) {
        return;
    }

    const std::size_t firstPartSize = randomSize(graph.vertexCount() - 2) + 1;
    addRandomEdges(graph, 0, firstPartSize);
    addRandomEdges(graph, firstPartSize, graph.vertexCount());
}

void GraphGenerator::addRandomEdges(Graph &graph, Graph::Vertex begin, Graph::Vertex end) {
    if (end - begin < 2) {
        return;
    }

    for (Graph::Vertex first = begin; first < end; ++first) {
        for (Graph::Vertex second = first + 1; second < end; ++second) {
            if (randomSize(1) == 1) {
                graph.addEdge(first, second);
            }
        }
    }
}

std::size_t GraphGenerator::randomSize(std::size_t maxInclusive) {
    return static_cast<std::size_t>(std::rand()) % (maxInclusive + 1);
}
