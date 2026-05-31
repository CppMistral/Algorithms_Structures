#include "graph.hpp"

#include <stack>

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
    std::vector<Vertex> tree;
    std::stack<Vertex> stack;

    visited.insert(startVertex);
    tree.push_back(startVertex);
    stack.push(startVertex);

    while (!stack.empty()) {
        const Vertex currentVertex = stack.top();
        stack.pop();

        for (Vertex neighbor : neighbors(currentVertex)) {
            if (!visited.contains(neighbor)) {
                continue;
            }

            visited.insert(neighbor);
            tree.push_back(neighbor);
            stack.push(neighbor);
        }
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

void Graph::print(std::ostream &out) const {
    out << "Список смежности:\n";
    for (Vertex vertex = 0; vertex < adjacencyLists_.size(); ++vertex) {
        out << vertex << ": ";
        for (Vertex neighbor : adjacencyLists_[vertex]) {
            out << neighbor << ' ';
        }
        out << '\n';
    }
}

bool Graph::isValidVertex(Vertex vertex) const {
    return vertex < adjacencyLists_.size();
}

bool Graph::SpanningForest::isGraphConnected() const {
    return forest_.size() <= 1;
}

void Graph::SpanningForest::addTree(std::vector<Vertex> tree) {
    forest_.push_back(std::move(tree));
}

void Graph::SpanningForest::print(std::ostream &out) const {
    out << "Деревья глубинного стягивающего леса: " << forest_.size() << '\n';
    for (const auto &tree : forest_) {
        for (std::size_t vertexIndex = 0; vertexIndex < tree.size(); ++vertexIndex) {
            if (vertexIndex > 0) {
                out << " - ";
            }
            out << tree[vertexIndex];
        }
        out << '\n';
    }
}
