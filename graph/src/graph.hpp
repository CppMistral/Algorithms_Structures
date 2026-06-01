#pragma once

#include <ostream>
#include <unordered_set>
#include <utility>
#include <vector>

class Graph {
  public:
    using Vertex = std::size_t;

    class SpanningForest {
      public:
        using Edge = std::pair<Vertex, Vertex>;
        using Tree = std::vector<Edge>;

        SpanningForest() = default;
        SpanningForest(const SpanningForest &) = delete;
        SpanningForest(SpanningForest &&) noexcept = default;
        ~SpanningForest() = default;

        SpanningForest &operator=(const SpanningForest &) = delete;
        SpanningForest &operator=(SpanningForest &&) noexcept = default;

        [[nodiscard]] bool isGraphConnected() const;

        void addTree(Tree tree);
        void print(std::ostream &output) const;
        void print() const;

      private:
        std::vector<Tree> forest_;
    };

    explicit Graph(std::size_t vertexCount = 0);
    Graph(const Graph &) = delete;
    Graph(Graph &&) noexcept = default;
    ~Graph() = default;

    Graph &operator=(const Graph &) = delete;
    Graph &operator=(Graph &&) noexcept = default;

    [[nodiscard]] std::size_t vertexCount() const;
    [[nodiscard]] const std::vector<Vertex> &neighbors(Vertex vertex) const;
    [[nodiscard]] SpanningForest spanningForest() const;

    bool addEdge(Vertex first, Vertex second);
    void print() const;

  private:
    std::vector<std::vector<Vertex>> adjacencyLists_;

    [[nodiscard]] bool isValidVertex(Vertex vertex) const;
    [[nodiscard]] SpanningForest::Tree DFS(Vertex startVertex,
                                           std::unordered_set<Graph::Vertex> &visited) const;
};
