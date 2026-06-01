#include "graph.hpp"

#include <iomanip>
#include <stack>
#include <string>

Graph::Graph(std::size_t vertexCount) : adjacencyLists_(vertexCount) {}

std::size_t Graph::vertexCount() const {
    return adjacencyLists_.size();
}

const std::vector<Graph::Vertex> &Graph::neighbors(Vertex vertex) const {
    return adjacencyLists_.at(vertex);
}

Graph::SpanningForest Graph::spanningForest() const {
    SpanningForest forest;
    std::unordered_set<Graph::Vertex> visited;

    for (Vertex vertex = 0; vertex < vertexCount(); ++vertex) {
        if (!visited.contains(vertex)) {
            forest.addTree(DFS(vertex, visited));
        }
    }

    return forest;
}

Graph::SpanningForest::Tree Graph::DFS(Vertex startVertex,
                                       std::unordered_set<Graph::Vertex> &visited) const {
    SpanningForest::Tree tree;
    std::stack<Vertex> stack;

    visited.insert(startVertex);
    stack.push(startVertex);

    while (!stack.empty()) {
        const Vertex currentVertex = stack.top();
        stack.pop();

        for (Vertex neighbor : neighbors(currentVertex)) {
            if (visited.contains(neighbor)) {
                continue;
            }

            visited.insert(neighbor);
            tree.emplace_back(currentVertex, neighbor);
            stack.push(neighbor);
        }
    }

    if (tree.empty()) {
        tree.emplace_back(startVertex, startVertex);
    }

    return tree;
}

bool Graph::addEdge(Vertex first, Vertex second) {
    if (!isValidVertex(first) || !isValidVertex(second) || first == second) {
        return false;
    }

    const auto &neighbors = adjacencyLists_[first];
    if (std::find(neighbors.begin(), neighbors.end(), second) != neighbors.end()) {
        return false;
    }

    adjacencyLists_[first].push_back(second);
    adjacencyLists_[second].push_back(first);

    return true;
}

void Graph::print() const {
    constexpr int CellWidth = 3;
    constexpr int LegendWidth = 3;

    std::cout << "Матрица смежности:\n";
    std::cout << std::setw(LegendWidth) << ' ' << " |";
    for (Vertex column = 0; column < adjacencyLists_.size(); ++column) {
        std::cout << std::setw(CellWidth) << column;
    }
    std::cout << '\n'
              << std::string(static_cast<std::size_t>(LegendWidth), '-') << "-+"
              << std::string(adjacencyLists_.size() * CellWidth, '-') << '\n';

    for (Vertex row = 0; row < adjacencyLists_.size(); ++row) {
        const auto &rowNeighbors = adjacencyLists_[row];

        std::cout << std::setw(LegendWidth) << row << " |";
        for (Vertex column = 0; column < adjacencyLists_.size(); ++column) {
            const bool hasEdge =
                std::find(rowNeighbors.begin(), rowNeighbors.end(), column) != rowNeighbors.end();
            std::cout << std::setw(CellWidth) << (hasEdge ? 1 : 0);
        }
        std::cout << '\n';
    }
}

bool Graph::isValidVertex(Vertex vertex) const {
    return vertex < adjacencyLists_.size();
}

bool Graph::SpanningForest::isGraphConnected() const {
    return forest_.size() <= 1;
}

void Graph::SpanningForest::addTree(Tree tree) {
    forest_.push_back(std::move(tree));
}

void Graph::SpanningForest::print(std::ostream &output) const {
    output << "Глубинный стягивающий лес\n";
    for (std::size_t treeIndex = 0; treeIndex < forest_.size(); ++treeIndex) {
        const auto &tree = forest_[treeIndex];
        output << "Дерево " << treeIndex + 1 << ": ";

        if (tree.size() == 1 && tree.front().first == tree.front().second) {
            output << tree.front().first;
        } else {
            for (std::size_t edgeIndex = 0; edgeIndex < tree.size(); ++edgeIndex) {
                if (edgeIndex > 0) {
                    output << ' ';
                }

                output << '(' << tree[edgeIndex].first << ", " << tree[edgeIndex].second << ')';
            }
        }

        output << '\n';
    }
}

void Graph::SpanningForest::print() const {
    print(std::cout);
}
