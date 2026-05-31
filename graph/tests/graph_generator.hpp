#pragma once

#include "graph.hpp"

#include <random>

class GraphGenerator {
  public:
    struct GeneratedGraph {
        Graph graph;
        std::size_t edgeCount = 0;
    };

    GraphGenerator();
    explicit GraphGenerator(unsigned seed);

    [[nodiscard]] GeneratedGraph generate(std::size_t vertexCount, bool forceConnected);

  private:
    std::mt19937 rng_;

    void generateConnected(GeneratedGraph &generated);
    void generateArbitrary(GeneratedGraph &generated);
    void addRandomEdges(GeneratedGraph &generated, std::size_t targetEdgeCount);

    [[nodiscard]] static std::size_t maxEdgeCount(std::size_t vertexCount);
};
