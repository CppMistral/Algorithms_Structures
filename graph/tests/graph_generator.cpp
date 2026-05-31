#include "graph_generator.hpp"

#include <algorithm>
#include <cstddef>
#include <random>
#include <unordered_set>

namespace {

std::size_t edgeKey(Graph::Vertex first, Graph::Vertex second, std::size_t vertexCount) {
    if (first > second) {
        std::swap(first, second);
    }

    return first * vertexCount + second;
}

bool addUniqueEdge(GraphGenerator::GeneratedGraph &generated, Graph::Vertex first,
                   Graph::Vertex second, std::unordered_set<std::size_t> &usedEdges) {
    const std::size_t key = edgeKey(first, second, generated.graph.vertexCount());
    if (first == second || usedEdges.contains(key)) {
        return false;
    }

    if (!generated.graph.addEdge(first, second)) {
        return false;
    }

    usedEdges.insert(key);
    ++generated.edgeCount;
    return true;
}

} // namespace

GraphGenerator::GraphGenerator() : rng_(std::random_device{}()) {}

GraphGenerator::GraphGenerator(unsigned seed) : rng_(seed) {}

GraphGenerator::GeneratedGraph GraphGenerator::generate(std::size_t vertexCount,
                                                        bool forceConnected) {
    GeneratedGraph generated{Graph(vertexCount), 0};
    if (vertexCount == 0) {
        return generated;
    }

    if (forceConnected) {
        generateConnected(generated);
    } else {
        generateArbitrary(generated);
    }

    return generated;
}

void GraphGenerator::generateConnected(GeneratedGraph &generated) {
    const std::size_t vertexCount = generated.graph.vertexCount();
    if (vertexCount < 2) {
        return;
    }

    std::unordered_set<std::size_t> usedEdges;
    for (Graph::Vertex vertex = 1; vertex < vertexCount; ++vertex) {
        std::uniform_int_distribution<Graph::Vertex> parentDistribution(0, vertex - 1);
        addUniqueEdge(generated, vertex, parentDistribution(rng_), usedEdges);
    }

    const std::size_t maxEdges = maxEdgeCount(vertexCount);
    const std::size_t remainingEdges = maxEdges - generated.edgeCount;
    const std::size_t extraLimit = std::min(remainingEdges, vertexCount);
    std::uniform_int_distribution<std::size_t> extraEdgesDistribution(0, extraLimit);

    addRandomEdges(generated, generated.edgeCount + extraEdgesDistribution(rng_));
}

void GraphGenerator::generateArbitrary(GeneratedGraph &generated) {
    const std::size_t maxEdges = maxEdgeCount(generated.graph.vertexCount());
    const std::size_t upperBound = maxEdges / 2;
    std::uniform_int_distribution<std::size_t> edgeCountDistribution(0, upperBound);

    addRandomEdges(generated, edgeCountDistribution(rng_));
}

void GraphGenerator::addRandomEdges(GeneratedGraph &generated, std::size_t targetEdgeCount) {
    const std::size_t maxEdges = maxEdgeCount(generated.graph.vertexCount());
    targetEdgeCount = std::min(targetEdgeCount, maxEdges);

    if (generated.graph.vertexCount() < 2) {
        return;
    }

    std::unordered_set<std::size_t> usedEdges;
    for (Graph::Vertex first = 0; first < generated.graph.vertexCount(); ++first) {
        for (Graph::Vertex second : generated.graph.neighbors(first)) {
            if (first < second) {
                usedEdges.insert(edgeKey(first, second, generated.graph.vertexCount()));
            }
        }
    }

    std::uniform_int_distribution<Graph::Vertex> vertexDistribution(
        0, generated.graph.vertexCount() - 1);
    std::size_t attempts = 0;
    const std::size_t maxAttempts = std::max<std::size_t>(100, maxEdges * 4);

    while (generated.edgeCount < targetEdgeCount && attempts < maxAttempts) {
        const Graph::Vertex first = vertexDistribution(rng_);
        const Graph::Vertex second = vertexDistribution(rng_);
        addUniqueEdge(generated, first, second, usedEdges);
        ++attempts;
    }

    for (Graph::Vertex first = 0;
         first < generated.graph.vertexCount() && generated.edgeCount < targetEdgeCount; ++first) {
        for (Graph::Vertex second = first + 1;
             second < generated.graph.vertexCount() && generated.edgeCount < targetEdgeCount;
             ++second) {
            addUniqueEdge(generated, first, second, usedEdges);
        }
    }
}

std::size_t GraphGenerator::maxEdgeCount(std::size_t vertexCount) {
    return vertexCount < 2 ? 0 : vertexCount * (vertexCount - 1) / 2;
}
