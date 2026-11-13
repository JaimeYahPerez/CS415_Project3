
++#ifndef STDTRIE_HPP
#define STDTRIE_HPP

#include <assert.h>
#include <vector>
#include <string>

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

void insert(const std::string& word, TreeNode& trie);



/*  TODO: move tester code from main and translate it
    to this insert function.

    Can't work on the search function until insert is completed
*/
void search(const std::string word);


#endif