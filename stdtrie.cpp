#include "stdtrie.hpp"



int char_to_index(char c) {
    return c - 97;
}



void insert(const std::string& word, TreeNode& trie) {
    TreeNode* current = &trie;

    for (char c : word) {
        int position = char_to_index(c);

        if (position < 0 || position >= 26) {
            throw std::invalid_argument(
                "Word must contain only a-z"
            );
        }

        if (current->child[position] == nullptr) {
            current->child[position] = new TreeNode;
        }

        current = current->child[position];
    }

    if (!word.empty()) {
        current->value = true;
    }
}



void search(const std::string word) {

}