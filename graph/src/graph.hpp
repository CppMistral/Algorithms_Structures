#pragma once

#include <iostream>
#include <unordered_set>
#include <vector>

class Graph {
  public:
    using Vertex = std::size_t;

    class SpanningForest {
      public:
        using Tree = std::vector<Vertex>;
        SpanningForest() = default;
        SpanningForest(const SpanningForest &other) = delete;
        SpanningForest(SpanningForest &&other) noexcept = default;
        ~SpanningForest() = default;

        SpanningForest &operator=(const SpanningForest &other) = default;
        SpanningForest &operator=(SpanningForest &&other) noexcept = default;

        [[nodiscard]] bool isGraphConnected() const;

        void addTree(std::vector<Vertex> tree);
        void print(std::ostream &out) const;

      private:
        std::vector<Tree> forest_;
    };

    explicit Graph(std::size_t vertexCount = 0);
    Graph(const Graph &other) = delete;
    Graph(Graph &&other) noexcept = delete;
    ~Graph() = default;

    Graph &operator=(const Graph &other) = delete;
    Graph &operator=(Graph &&other) noexcept = delete;

    [[nodiscard]] std::size_t vertexCount() const;
    [[nodiscard]] const std::vector<Vertex> &neighbors(Vertex vertex) const;
    [[nodiscard]] SpanningForest spanningForest() const;

    bool addEdge(Vertex first, Vertex second);
    void print(std::ostream &out) const;

  private:
    std::vector<std::vector<Vertex>> adjacencyLists_;

    [[nodiscard]] bool isValidVertex(Vertex vertex) const;
    [[nodiscard]] SpanningForest::Tree DFS(Vertex startVertex,
                                           std::unordered_set<Graph::Vertex> &visited) const;
};
