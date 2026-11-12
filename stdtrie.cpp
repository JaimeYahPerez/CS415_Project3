#include "stdtrie.hpp"



int char_to_index(char c) {
    return c - 97;
}



void insert(const std::string& word, TreeNode& trie, int& t_ops, int& s_ops) {
    if (word.empty()) {
        return;
    }
    
    insert_helper(word, &trie, 0, t_ops, s_ops);
    //std::cout << "Time taken to build the standard Trie is" << ops << "operations and space occupied by it is " << ops << "pointer units\n";
}

void insert_helper(const std::string& word, TreeNode* trie, std::size_t index, int& t_ops, int& s_ops) {

    // Base case: reached the end of the word.
    if (index == word.length()) {
        trie->value = true;
        t_ops++;
        return;
    }

    // Find the character's position.
    int position = char_to_index(word[index]);

    // Validate the character.
    if (position < 0 || position >= 26) {
        throw std::invalid_argument("Word must contain only a-z");
    }

    // Create the child if it doesn't exist.
    if (trie->child[position] == nullptr) {
        trie->child[position] = new TreeNode;
        s_ops++;
    }

    // Continue to the next character.
    insert_helper(word, trie->child[position], index + 1, t_ops, s_ops);
}


void search(const std::string word, TreeNode& trie) {
    if (word.empty()) {
        return;
    }
    int start = 0;
    int ops = 0;
    search_helper(word, &trie, start, ops);

}
void search_helper(const std::string word, TreeNode* trie, int index, int& ops) {
    // base case: if index is null, increment ops and exit
    //int pos = char_to_index(word[index]);
    
    
    // otherwise, increment index and ops and call search(word, index + 1, ops)
    
}