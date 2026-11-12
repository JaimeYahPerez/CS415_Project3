#include "stdtrie.hpp"



int char_to_index(char c) {
    return c - 97;
}



void insert(const std::string& word, TreeNode& trie) {
    if (word.empty()) {
        return;
    }

    insert_helper(word, &trie, 0);
}

void insert_helper(const std::string& word, TreeNode* trie, std::size_t index) {

    // Base case: reached the end of the word.
    if (index == word.length()) {
        trie->value = true;
        return;
    }

    // Find the character's position.
    int position = char_to_index(word[index]);

    // Validate the character.
    if (position < 0 || position >= 26) {
        throw std::invalid_argument(
            "Word must contain only a-z"
        );
    }

    // Create the child if it doesn't exist.
    if (trie->child[position] == nullptr) {
        trie->child[position] = new TreeNode;
    }

    // Continue to the next character.
    insert_helper(word, trie->child[position], index + 1);
}



void search(const std::string word) {

}