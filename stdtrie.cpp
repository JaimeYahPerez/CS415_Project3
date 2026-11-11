#include "stdtrie.hpp"



int char_to_index(char c) {
    return c - 97;
}


void insert(std::string word, TreeNode& trie) {

    // assertion: word is of length greather than 0
    assert(word.length() > 0);

    //int index = word.length();

    int position = char_to_index(word[0]);

    if (trie.child[position] == nullptr) {
        trie.child[position] = new TreeNode;
    }

    word.erase(word.begin());

    // if word's length is now empty, set the end of word value to true
    if (word.length() == 0) 
    {
        trie.child[position]->value = true;
    } 
    else {insert_helper(word, trie.child[position]);} 

}

void insert_helper(std::string word, TreeNode* trie) {

    // base case: when length is 1, create TreeNode*
    // and mark the end of word value to true

    int position = char_to_index(word[0]);

    if (trie->child[position] == nullptr) {
        trie->child[position] = new TreeNode;
    }

    if (word.length() == 1) 
    {
        trie->child[position]->value = true;
        return;
    }

    // else, delete the first character of the current word and continue forward

    word.erase(word.begin());

    insert_helper(word, trie->child[position]);

}


void search(const std::string word) {

}