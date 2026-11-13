
#ifndef STDTRIE_HPP
#define STDTRIE_HPP

//#include <iostream>
#include <assert.h>
#include <vector>
#include <string>
#include <stdexcept>
#include <iostream>

struct TreeNode {
    bool value = false;

    std::vector<TreeNode*> child = std::vector<TreeNode*>(26, nullptr);
};

// assuming the char is between a to z, returns it's index value
int char_to_index(char c);


/*  TODO: move tester code from main and translate it
    to this insert function.
    
    May change VOID to INT to the look up counts.

    Can't work on the search function until insert is completed
*/

void insert(const std::string& word, TreeNode& trie, int& t_ops, int& s_ops);



/*  TODO: move tester code from main and translate it
    to this insert function.

    Can't work on the search function until insert is completed
*/
void search(const std::string word, TreeNode& trie, int& ops);
void search_helper(const std::string word, TreeNode* trie, int index, int& count);

void autocomplete(const std::string& word, TreeNode* trie, int& ops);
void autocomplete_helper(TreeNode* trie, std::string& currentWord, std::vector<std::string>& results, int& ops);

#endif