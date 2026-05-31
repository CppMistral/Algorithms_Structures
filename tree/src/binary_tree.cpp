#include "binary_tree.hpp"

#include <algorithm>
#include <chrono>
#include <iostream>
#include <limits>
#include <queue>

namespace {
constexpr int SCREEN_COLUMNS = 80;
}

std::unique_ptr<BinaryTree::Node> BinaryTree::makeNode(int &nextId) {
    return std::make_unique<Node>(nextId++);
}

BinaryTree BinaryTree::buildSample() {
    int nextId = 1;
    BinaryTree tree;
    tree.root_ = makeNode(nextId);
    tree.root_->left_ = makeNode(nextId);
    tree.root_->right_ = makeNode(nextId);
    tree.root_->left_->left_ = makeNode(nextId);
    tree.root_->left_->right_ = makeNode(nextId);
    tree.root_->right_->right_ = makeNode(nextId);
    tree.root_->left_->right_->left_ = makeNode(nextId);

    tree.markSymmetric();
    return tree;
}

BinaryTree BinaryTree::buildManual() {
    int nextId = 1;
    BinaryTree tree;
    std::cout << "Введите структуру дерева. 1 - создать вершину, 0 - пропустить.\n";
    tree.root_ = buildManualNode(nextId, 0, "корень");
    tree.markSymmetric();
    return tree;
}

BinaryTree BinaryTree::buildRandom() {
    int nextId = 1;
    BinaryTree tree;
    const auto seed =
        static_cast<unsigned>(std::chrono::steady_clock::now().time_since_epoch().count());
    std::mt19937 gen(seed);
    tree.root_ = buildRandomNode(nextId, 0, 4, gen);
    tree.markSymmetric();
    return tree;
}

std::unique_ptr<BinaryTree::Node> BinaryTree::buildManualNode(int &nextId, int depth,
                                                              const std::string &position) {
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

    auto node = makeNode(nextId);
    node->left_ =
        buildManualNode(nextId, depth + 1, "левый потомок вершины " + std::to_string(node->id_));
    node->right_ =
        buildManualNode(nextId, depth + 1, "правый потомок вершины " + std::to_string(node->id_));
    return node;
}

std::unique_ptr<BinaryTree::Node> BinaryTree::buildRandomNode(int &nextId, int depth, int maxDepth,
                                                              std::mt19937 &gen) {
    if (depth > maxDepth) {
        return nullptr;
    }

    std::bernoulli_distribution shouldCreate(depth == 0 ? 1.0 : std::max(0.2, 0.85 - depth * 0.15));
    if (!shouldCreate(gen)) {
        return nullptr;
    }

    auto node = makeNode(nextId);
    node->left_ = buildRandomNode(nextId, depth + 1, maxDepth, gen);
    node->right_ = buildRandomNode(nextId, depth + 1, maxDepth, gen);
    return node;
}

void BinaryTree::markSymmetric() {
    nextLabel_ = 'A';
    markSymmetric(root_.get());
    calculateDescendants(root_.get());
}

void BinaryTree::markSymmetric(Node *node) {
    if (node == nullptr) {
        return;
    }

    markSymmetric(node->left_.get());
    node->label_ = nextLabel_++;
    markSymmetric(node->right_.get());
}

int BinaryTree::calculateDescendants(Node *node) {
    if (node == nullptr) {
        return 0;
    }

    const int leftSize = calculateDescendants(node->left_.get());
    const int rightSize = calculateDescendants(node->right_.get());
    node->descendants_ = leftSize + rightSize;
    return node->descendants_ + 1;
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
    screen[row][column] = node->label_;

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

void BinaryTree::printBreadthFirst() const {
    const std::vector<const Node *> nodes = breadthFirstNodes();
    std::cout << "Обход в ширину: ";
    for (std::size_t i = 0; i < nodes.size(); ++i) {
        if (i != 0) {
            std::cout << ' ';
        }
        std::cout << nodes[i]->label_;
    }
    std::cout << '\n';
}

void BinaryTree::printDescendants() const {
    std::cout << "Количество потомков у каждой вершины:\n";
    for (const Node *node : breadthFirstNodes()) {
        std::cout << "  " << node->label_ << ": " << node->descendants_ << '\n';
    }
}
