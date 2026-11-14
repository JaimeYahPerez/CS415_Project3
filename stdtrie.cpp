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


void search(const std::string word, TreeNode& trie, int& ops) {
    if (word.empty()) {
        return;
    }
    int start = 0;
    search_helper(word, &trie, start, ops);

}

void search_helper(const std::string word, TreeNode* trie, int index, int& ops) {
    // base case: if index is null, increment ops and exit
    //int pos = char_to_index(word[index]);

    if (index == word.length()) {
        if (trie->value == true) {
            ops++;
            return;
        } else {
            ops++;
            printf("Your word is not in this trie.\n");
            return;
        } 
    }

    int position = char_to_index(word[index]);

    if (trie->child[position] == nullptr) {
        ops++;
        printf("Your word is not in this trie.\n");
        return;
    }
    
     // Validate the character.
    if (position < 0 || position >= 26) {
        throw std::invalid_argument("Word must contain only a-z");
    }

    // If there is still more to travel, ncrement index and ops and call search(word, index + 1, ops)
    ops++;
    search_helper(word, trie->child[position], index + 1, ops);
    
}


void autocomplete_helper(TreeNode* trie, std::string& currentWord, std::vector<std::string>& results, int& ops) {
    if (trie == nullptr) {
        return;
    }

    // If this node represents a complete word, save it.
    if (trie->value == true) {
        results.push_back(currentWord);
    }

    // Explore all possible children (a-z).
    for (int i = 0; i < 26; i++) {
        ops++;
        if (trie->child[i] != nullptr) {

            

            currentWord.push_back('a' + i);

            autocomplete_helper(trie->child[i], currentWord, results, ops);

            // Backtrackin' time!
            currentWord.pop_back();
        }
    }
}

void autocomplete(const std::string& word, TreeNode* trie, int& ops) {
    TreeNode* current = trie;

    // Find the node corresponding to the prefix.
    for (int i = 0; i < word.length(); i++) {

        int position = char_to_index(word[i]);

        if (position < 0 || position >= 26) {
            throw std::invalid_argument(
                "Word must contain only a-z"
            );
        }

        ops++;

        if (current->child[position] == nullptr) {
            printf("No autocomplete results found.\n");
            return;
        }

        current = current->child[position];
    }

    // Find all words beginning with the prefix.
    std::vector<std::string> results;
    std::string currentWord = word;

    autocomplete_helper(current, currentWord, results, ops);

    // Print autocomplete results.
    if (results.empty()) {
        std::cout << "No autocomplete results found.\n";
    }
    else {
        std::cout << "Auto-complete results using standard Trie are: ";
        for (const std::string& result : results) {
            std::cout << result << ",";
        }
        std::cout << std::endl;
    }
}