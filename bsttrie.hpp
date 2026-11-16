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

   

    

    // Construction measurements
    int getBuildOperations() const;
    int getNodeCount() const;
    int getPointerUnits() const;
    int getSearchOperations() const;
    int getAutocompleteOperations() const;





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

    int buildOperations_ = 0;
    int nodeCount_ = 0;
    int searchOperations_ = 0;
    int autocompleteOperations_ = 0;

    // Helper functions for AVL
    static int getHeight(Node* node);
    static int getBalanceFactor(Node* node);
    static void updateHeight(Node* node);
    
    Node* rotateLeft(Node* node);
    Node* rotateRight(Node* node);
    Node* balance(Node* node);

    Node* findPrefix(Node* node, const std::string& prefix, std::size_t index);

    void collectWords(Node* node, std::string& currentWord);


    static void destroy(Node* node);
};

#endif
