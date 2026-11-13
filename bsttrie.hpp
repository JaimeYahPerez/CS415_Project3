#pragma once

#ifndef BSTTRIE_HPP
#define BSTTRIE_HPP

#include <cstdint>
#include <string>

class BSTTrie {
public:
    BSTTrie() = default;
    ~BSTTrie();

    // Prevent accidental copying of owned pointers.
    BSTTrie(const BSTTrie&) = delete;
    BSTTrie& operator=(const BSTTrie&) = delete;
    BSTTrie(BSTTrie&&) = delete;
    BSTTrie& operator=(BSTTrie&&) = delete;

    // Insert a normalized a-z word.
    void insert(const std::string& word);

    // Construction measurements.
    std::uint64_t getBuildOperations() const;
    std::uint64_t getNodeCount() const;
    std::uint64_t getPointerUnits() const;

private:
    struct Node {
        explicit Node(char c) : character(c) {}

        char character;
        bool isWord = false;

        Node* left = nullptr;
        Node* middle = nullptr;
        Node* right = nullptr;
    };

    Node* root_ = nullptr;

    std::uint64_t buildOperations_ = 0;
    std::uint64_t nodeCount_ = 0;

    static void destroy(Node* node);
};

#endif
