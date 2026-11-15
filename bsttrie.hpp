#pragma once

#ifndef BSTTRIE_HPP
#define BSTTRIE_HPP

#include <cstdint>
#include <string>
#include <vector>

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

    void search(const std::string& word);

    void autocomplete(const std::string& prefix);

   

    

    // Construction measurements.
    std::uint64_t getBuildOperations() const;
    std::uint64_t getNodeCount() const;
    std::uint64_t getPointerUnits() const;
    std::uint64_t getSearchOperations() const;
    std::uint64_t getAutocompleteOperations() const;





private:
    struct Node {
        explicit Node(char c) : character(c) {}

        char character;
        bool isWord = false;

        Node* left = nullptr;
        Node* middle = nullptr;
        Node* right = nullptr;

        // to balance the tree, we need to update height across the nodes
        int height = 1;
    };

    Node* root_ = nullptr;

    std::uint64_t buildOperations_ = 0;
    std::uint64_t nodeCount_ = 0;
    std::uint64_t searchOperations_ = 0;
    std::uint64_t autocompleteOperations_ = 0;

    // Helper functions for AVL
    static int getHeight(Node* node);
    static int getBalanceFactor(Node* node);
    static void updateHeight(Node* node);
    
    static Node* rotateLeft(Node* node);
    static Node* rotateRight(Node* node);
    static Node* balance(Node* node);

    Node* findPrefix(Node* node, const std::string& prefix, std::size_t index);

    void collectWords(Node* node, std::string& currentWord);


    static void destroy(Node* node);
};

#endif
