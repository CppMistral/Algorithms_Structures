#pragma once

#include "graph.hpp"

class GraphGenerator {
  public:
    static constexpr std::size_t MaxVertexCount = 20;

    GraphGenerator();
    GraphGenerator(const GraphGenerator &) = delete;
    GraphGenerator(GraphGenerator &&) noexcept = delete;
    ~GraphGenerator() = default;

    GraphGenerator &operator=(const GraphGenerator &) = delete;
    GraphGenerator &operator=(GraphGenerator &&) noexcept = delete;

    Graph generateRandom(bool connected = true);

  private:
    void generateConnected(Graph &graph);
    void generateDisconnected(Graph &graph);
    void addRandomEdges(Graph &graph, Graph::Vertex begin, Graph::Vertex end);

    static std::size_t randomSize(std::size_t maxInclusive);
};
