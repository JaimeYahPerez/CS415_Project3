
#include "bsttrie.hpp"

#include <stdexcept>
#include <algorithm>
#include <iostream>

void BSTTrie::insert(const std::string& word) {

    if (word.empty()) {
        return;
    }

    // Validating if the char is valid
    for (char c : word) {
        if (c < 'a' || c > 'z') {
            throw std::invalid_argument(
                "BSTTrie expects normalized a-z words"
            );
        }
    }
    
    std::vector<Node**> path;

    Node** link = &root_;

    std::size_t index = 0;

    while (index < word.size()) {

        if (*link == nullptr) {

            *link = new Node(word[index]);

            ++nodeCount_;
            ++buildOperations_;
            ++buildOperations_;

        }

        Node* current = *link;

        ++buildOperations_;

        if (word[index] < current->character) {

            path.push_back(link);
            link = &current->left;

        }
        else if (word[index] > current->character) {

            ++buildOperations_;

            path.push_back(link);
            link = &current->right;

        }
        else {
            ++buildOperations_;

            ++index;

            if (index == word.size()) {

                ++buildOperations_;

                if (!current->isWord) {
                    current->isWord = true;
                    ++buildOperations_;
                }

                break;
            }

            link = &current->middle;
        }
    }

    // Balance all affected BST levels.
    for (auto it = path.rbegin(); it != path.rend(); ++it) {

        Node** subtreeLink = *it;

        Node* updated = balance(*subtreeLink);

        if (updated != *subtreeLink) {
            *subtreeLink = updated;
            ++buildOperations_;
        }
    }
}

// Below are the height functions for the AVL


int BSTTrie::getHeight(Node* node) {
    return node == nullptr ? 0 : node->height;
}

int BSTTrie::getBalanceFactor(Node* node) {
    if (node == nullptr) {
        return 0;
    }

    return getHeight(node->left) - getHeight(node->right);
}

void BSTTrie::updateHeight(Node* node) {
    if (node == nullptr) {
        return;
    }

    node->height = 1 + std::max(
        getHeight(node->left),
        getHeight(node->right)
    );
}

// AVL Rotation functions 

BSTTrie::Node* BSTTrie::rotateRight(Node* node) {
    Node* pivot = node->left;
    Node* transfer = pivot->right;

    pivot->right = node;
    node->left = transfer;
    buildOperations_ += 2;


    updateHeight(node);
    updateHeight(pivot);

    return pivot;
}

BSTTrie::Node* BSTTrie::rotateLeft(Node* node) {
    Node* pivot = node->right;
    Node* transfer = pivot->left;

    pivot->left = node;
    node->right = transfer;
    buildOperations_ += 2;

    updateHeight(node);
    updateHeight(pivot);

    return pivot;
}

// AVL Balancing

BSTTrie::Node* BSTTrie::balance(Node* node) {
    if (node == nullptr) {
        return nullptr;
    }

    updateHeight(node);

    int bf = getBalanceFactor(node);

    // Left-heavy.
    if (bf > 1) {

        // Left-right case.
        if (getBalanceFactor(node->left) < 0) {
            node->left = rotateLeft(node->left);
            ++buildOperations_;
        }

        // Left-left case.
        return rotateRight(node);
    }

    // Right-heavy.
    if (bf < -1) {

        // Right-left case.
        if (getBalanceFactor(node->right) > 0) {
            node->right = rotateRight(node->right);
            ++buildOperations_;
        }

        // Right-right case.
        return rotateLeft(node);
    }

    return node;
}


// Destructor
BSTTrie::~BSTTrie() {
    destroy(root_);
}

// Recursive cleanup
void BSTTrie::destroy(Node* node) {
    if (node == nullptr) {
        return;
    }

    destroy(node->left);
    destroy(node->middle);
    destroy(node->right);

    delete node;
}

void BSTTrie::search(const std::string& word) {

    searchOperations_ = 0;

    if (word.empty()) {
        return;
    }

    Node* current = root_;
    int index = 0;

    while (current != nullptr) {

        char c = word[index];

        // Count the first comparison.
        ++searchOperations_;

        if (c < current->character) {
            current = current->left;
            continue;
        }

        // Count the second comparison.
        ++searchOperations_;

        if (c > current->character) {
            current = current->right;
            continue;
        }

        // Characters match.
        ++index;

        if (index == word.size()) {
            ++searchOperations_; // Inspect word-ending marker.
            return;
        }

        current = current->middle;
    }
}

BSTTrie::Node* BSTTrie::findPrefix( Node* node, const std::string& prefix,std::size_t index ) {
    // Count node visit.
    ++autocompleteOperations_;

    if (node == nullptr) {
        return nullptr;
    }

    char c = prefix[index];

    // First character comparison.
    ++autocompleteOperations_;

    if (c < node->character) {
        ++autocompleteOperations_; // Pointer traversal
        return findPrefix(node->left, prefix, index);
    }

    // Second character comparison.
    ++autocompleteOperations_;

    if (c > node->character) {
        ++autocompleteOperations_; // Pointer traversal
        return findPrefix(node->right, prefix, index);
    }

    // Character matched.
    ++autocompleteOperations_;

    if (index == prefix.size() - 1) {
        return node;
    }

    // Move to next character.
    ++autocompleteOperations_;

    return findPrefix(node->middle, prefix, index + 1);
}

void BSTTrie::collectWords( Node* node,std::string& currentWord ) {
    // Count node visit.
    ++autocompleteOperations_;

    if (node == nullptr) {
        return;
    }

    // Traverse left subtree.
    ++autocompleteOperations_;
    collectWords(node->left, currentWord);

    // Add current character.
    currentWord.push_back(node->character);
    ++autocompleteOperations_;

    // Check if this is a complete word.
    ++autocompleteOperations_;

    if (node->isWord) {
        std::cout << currentWord << ", ";
    }

    // Traverse middle subtree.
    ++autocompleteOperations_;
    collectWords(node->middle, currentWord);

    // Remove current character.
    currentWord.pop_back();
    ++autocompleteOperations_;

    // Traverse right subtree.
    ++autocompleteOperations_;
    collectWords(node->right, currentWord);
}

void BSTTrie::autocomplete(const std::string& prefix) {

    // Reset counter for each autocomplete.
    autocompleteOperations_ = 0;

    if (prefix.empty()) {
        return;
    }

    // Find the final character of the prefix.
    Node* prefixNode = findPrefix(root_, prefix, 0);

    if (prefixNode == nullptr) {
        std::cout << "No autocomplete results found.\n";
        return;
    }

    // Start with the query.
    std::string currentWord = prefix;

    // Print the query if it is already a complete word.
    ++autocompleteOperations_;

    if (prefixNode->isWord) {
        std::cout << currentWord << ", ";
    }

    // Collect all words beginning with the prefix.
    ++autocompleteOperations_;
    collectWords(prefixNode->middle, currentWord);
}




// Recursively collect words in the BST level.

int BSTTrie::getSearchOperations() const {
    return searchOperations_;
}

// Construction measurements
int BSTTrie::getBuildOperations() const {
    return buildOperations_;
}

int BSTTrie::getNodeCount() const {
    return nodeCount_;
}

int BSTTrie::getPointerUnits() const {
    return 3 * nodeCount_;
}

int BSTTrie::getAutocompleteOperations() const {
    return autocompleteOperations_;
}
