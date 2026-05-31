#pragma once

#include <memory>
#include <random>
#include <string>
#include <vector>

class BinaryTree {
  public:
    struct Node {
        explicit Node(int id) : id_(id) {}

        int id_ = 0;
        char label_ = '?';
        int descendants_ = 0;
        std::unique_ptr<Node> left_;
        std::unique_ptr<Node> right_;
    };

    [[nodiscard]] static BinaryTree buildSample();
    [[nodiscard]] static BinaryTree buildManual();
    [[nodiscard]] static BinaryTree buildRandom();

    [[nodiscard]] bool empty() const {
        return root_ == nullptr;
    }

    void print() const;
    void printBreadthFirst() const;
    void printDescendants() const;

  private:
    std::unique_ptr<Node> root_;
    char nextLabel_ = 'A';

    static std::unique_ptr<Node> makeNode(int &nextId);
    static std::unique_ptr<Node> buildManualNode(int &nextId, int depth,
                                                 const std::string &position);
    static std::unique_ptr<Node> buildRandomNode(int &nextId, int depth, int maxDepth,
                                                 std::mt19937 &gen);

    void markSymmetric();
    void markSymmetric(Node *node);
    int calculateDescendants(Node *node);

    [[nodiscard]] int height(const Node *node) const;
    void placeNode(const Node *node, std::vector<std::string> &screen, int row, int leftColumn,
                   int rightColumn) const;
    [[nodiscard]] std::vector<const Node *> breadthFirstNodes() const;
};
