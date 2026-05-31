#include "binary_tree.hpp"

#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>
#include <unordered_map>

inline constexpr int SCREEN_COLUMNS = 80;

std::unique_ptr<BinaryTree::Node> BinaryTree::makeNode(Node *parent) {
    auto node = std::make_unique<Node>();
    node->parent_ = parent;
    return node;
}

BinaryTree BinaryTree::buildTest() {
    BinaryTree tree;
    tree.root_ = makeNode();
    tree.root_->left_ = makeNode(tree.root_.get());
    tree.root_->right_ = makeNode(tree.root_.get());
    tree.root_->left_->left_ = makeNode(tree.root_->left_.get());
    tree.root_->left_->right_ = makeNode(tree.root_->left_.get());
    tree.root_->right_->right_ = makeNode(tree.root_->right_.get());
    tree.root_->left_->right_->left_ = makeNode(tree.root_->left_->right_.get());

    tree.markSymmetric();
    return tree;
}

BinaryTree BinaryTree::buildManual() {
    BinaryTree tree;
    std::cout << "Введите структуру дерева. 1 - создать вершину, 0 - пропустить.\n";
    tree.root_ = buildManualNode(0, "корень");
    tree.markSymmetric();
    return tree;
}

std::unique_ptr<BinaryTree::Node>
BinaryTree::buildManualNode(int depth, const std::string &position, Node *parent) {
    int answer = 0;
    do {
        std::cout << position << ", глубина " << depth << " (1/0): ";
        if (!(std::cin >> answer)) {
            if (std::cin.eof()) {
                return nullptr;
            }
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            answer = -1;
        }
    } while (answer != 0 && answer != 1);

    if (answer == 0) {
        return nullptr;
    }

    auto node = makeNode(parent);
    node->left_ = buildManualNode(depth + 1, "левый потомок узла \"" + position + "\"", node.get());
    node->right_ =
        buildManualNode(depth + 1, "правый потомок узла \"" + position + "\"", node.get());
    return node;
}

void BinaryTree::markSymmetric() {
    nextTag_ = 'A';
    markSymmetric(root_.get());
}

void BinaryTree::markSymmetric(Node *node) {
    if (node == nullptr) {
        return;
    }

    markSymmetric(node->left_.get());
    node->tag_ = nextTag_++;
    markSymmetric(node->right_.get());
}

std::unordered_map<const BinaryTree::Node *, int>
BinaryTree::countDescendants(const std::vector<const Node *> &nodes) {
    std::unordered_map<const Node *, int> descendantsByNode;

    for (auto it = nodes.rbegin(); it != nodes.rend(); ++it) {
        const Node *node = *it;
        descendantsByNode.try_emplace(node, 0);

        const Node *parent = node->parent_;
        if (parent != nullptr) {
            descendantsByNode[parent] += descendantsByNode[node] + 1;
        }
    }

    return descendantsByNode;
}

void BinaryTree::print() const {
    if (empty()) {
        std::cout << "Дерево пусто.\n";
        return;
    }

    std::cout << "Изображение дерева с симметричной разметкой:\n";
    const int rows = height(root_.get());
    std::vector<std::string> screen(rows, std::string(SCREEN_COLUMNS, '.'));

    placeNode(root_.get(), screen, 0, 0, SCREEN_COLUMNS - 1);
    for (const std::string &line : screen) {
        std::cout << line << '\n';
    }

    std::cout << '\n';
    const std::vector<const Node *> nodes = breadthFirstNodes();
    const std::unordered_map<const Node *, int> descendantsByNode = countDescendants(nodes);

    std::cout << "Обход в ширину: ";
    for (std::size_t i = 0; i < nodes.size(); ++i) {
        if (i != 0) {
            std::cout << ' ';
        }
        std::cout << nodes[i]->tag_;
    }
    std::cout << '\n';

    std::cout << "Количество потомков у каждой вершины:\n";
    for (const Node *node : nodes) {
        std::cout << "  " << node->tag_ << ": " << descendantsByNode.at(node) << '\n';
    }
}

int BinaryTree::height(const Node *node) const {
    if (node == nullptr) {
        return 0;
    }

    return 1 + std::max(height(node->left_.get()), height(node->right_.get()));
}

void BinaryTree::placeNode(const Node *node, std::vector<std::string> &screen, int row,
                           int leftColumn, int rightColumn) const {
    if (node == nullptr || leftColumn > rightColumn) {
        return;
    }

    const int column = (leftColumn + rightColumn) / 2;
    screen[row][column] = node->tag_;

    placeNode(node->left_.get(), screen, row + 1, leftColumn, column - 1);
    placeNode(node->right_.get(), screen, row + 1, column + 1, rightColumn);
}

std::vector<const BinaryTree::Node *> BinaryTree::breadthFirstNodes() const {
    std::vector<const Node *> result;
    if (root_ == nullptr) {
        return result;
    }

    std::queue<const Node *> queue;
    queue.push(root_.get());

    while (!queue.empty()) {
        const Node *node = queue.front();
        queue.pop();
        result.push_back(node);

        if (node->left_ != nullptr) {
            queue.push(node->left_.get());
        }
        if (node->right_ != nullptr) {
            queue.push(node->right_.get());
        }
    }

    return result;
}
