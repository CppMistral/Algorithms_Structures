#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

class BinaryTree {
  public:
    struct Node {
        char tag_ = '.';
        Node *parent_ = nullptr;
        std::unique_ptr<Node> left_;
        std::unique_ptr<Node> right_;
    };

    [[nodiscard]] static BinaryTree buildTest();
    [[nodiscard]] static BinaryTree buildManual();

    [[nodiscard]] bool empty() const {
        return root_ == nullptr;
    }

    void print() const;

  private:
    std::unique_ptr<Node> root_;
    char nextTag_ = 'A';

    static std::unique_ptr<Node> makeNode(Node *parent = nullptr);
    static std::unique_ptr<Node> buildManualNode(int depth, const std::string &position,
                                                 Node *parent = nullptr);

    void markSymmetric();
    void markSymmetric(Node *node);
    [[nodiscard]] static std::unordered_map<const Node *, int>
    countDescendants(const std::vector<const Node *> &nodes);

    [[nodiscard]] int height(const Node *node) const;
    void placeNode(const Node *node, std::vector<std::string> &screen, int row, int leftColumn,
                   int rightColumn) const;
    [[nodiscard]] std::vector<const Node *> breadthFirstNodes() const;
};
