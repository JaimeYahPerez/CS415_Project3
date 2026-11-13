
#include "bsttrie.hpp"

#include <stdexcept>

void BSTTrie::insert(const std::string& word) {
    if (word.empty()) {
        return;
    }

    // Validate before inserting.
    for (char c : word) {
        if (c < 'a' || c > 'z') {
            throw std::invalid_argument(
                "BSTTrie expects normalized a-z words"
            );
        }
    }

    Node** link = &root_;
    std::size_t index = 0;

    while (true) {
        const char c = word[index];

        // Create a new node if necessary.
        if (*link == nullptr) {
            *link = new Node(c);

            ++nodeCount_;
            ++buildOperations_; // Node creation
            ++buildOperations_; // Pointer assignment
        }

        Node* current = *link;

        // Compare against the current node character.
        ++buildOperations_;
        if (c < current->character) {
            link = &current->left;
            continue;
        }

        ++buildOperations_;
        if (c > current->character) {
            link = &current->right;
            continue;
        }

        // Equal: move to the next word character.
        ++index;

        // Reached the final character?
        if (index == word.size()) {
            ++buildOperations_; // Check ending marker

            if (!current->isWord) {
                current->isWord = true;
                ++buildOperations_; // Update marker
            }

            break;
        }

        link = &current->middle;
    }
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

// Construction measurements
std::uint64_t BSTTrie::getBuildOperations() const {
    return buildOperations_;
}

std::uint64_t BSTTrie::getNodeCount() const {
    return nodeCount_;
}

std::uint64_t BSTTrie::getPointerUnits() const {
    return 3 * nodeCount_;
}
