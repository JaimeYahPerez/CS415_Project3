
#include "input.hpp"
#include "stdtrie.hpp"
#include "bsttrie.hpp"

#include <exception>
#include <iostream>
#include <string>

// Flag 1: accept queries until EOF or Ctrl-C.
void runQueryMode(TreeNode& trie, BSTTrie& bst) {
    std::string rawQuery;

    int search_ops_trie = 0;
    int autocomplete_ops_trie = 0;

    while (true) {
        std::cout << "Enter search string: " << std::flush;

        if (!(std::cin >> rawQuery)) {
            std::cout << '\n';
            break;
        }

        // Normalize the user's query.
        const std::string query = normalizeWord(rawQuery);

        if (query.empty()) {
            std::cout << "Please enter a query containing letters.\n";
            continue;
        }

        // Search standard Trie
        search(query, trie, search_ops_trie);
        std::cout << "Time taken to search in the standard Trie is " << search_ops_trie << " operations.\n";
        search_ops_trie = 0; // reset for next while loop
        
        // Prints and displays the autocomplete query for standard trie 
        autocomplete(query, &trie, autocomplete_ops_trie);
        std::cout<< "Time taken to find auto-complete results in the standard Trie is " << autocomplete_ops_trie << " opertions.\n";
        autocomplete_ops_trie = 0; // reset for next loop
       
        std::cout << std::endl;

        // Prints and displays the autocomplete query for BST-based trie 
        bst.search(query);
        std::cout << "Time taken to search in the BST based Trie is " << bst.getSearchOperations() << " operations.\n";
        std::cout << "Auto-complete results using BST based Trie: ";
        bst.autocomplete(query);
        std::cout << std::endl;
        std::cout<< "Time taken to find auto-complete results in the standard Trie is " << bst.getAutocompleteOperations() << " opertions.\n";

        std::cout << std::endl;
    }
}

// Flag 2: search every word from the input file.
void runAllWordsMode(const InputData& data, TreeNode& trie, BSTTrie& bst) {

    int totalSearchOperationsTrie = 0;
    int totalSearchOperationsBST = 0;

    // Search every word in the standard Trie.
    for (const std::string& word : data.words) {

        int searchOperations = 0;

        search(word, trie, searchOperations);

        totalSearchOperationsTrie += searchOperations;
    }

    // Search every word in the BST-based Trie.
    for (const std::string& word : data.words) {

        bst.search(word);

        totalSearchOperationsBST += bst.getSearchOperations();
    }

    // Print total operation counts.
    std::cout << "Time taken to search all the strings in the standard Trie is "
              << totalSearchOperationsTrie << " operations.\n";

    std::cout << "Time taken to search all the strings in the BST based Trie is "
              << totalSearchOperationsBST << " operations.\n";
}

int main(int argc, char* argv[]) {
    // Verify command-line arguments.
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0]
            << " <input_file> <1|2>\n";
        return 1;
    }

    const std::string flag = argv[2];

    if (flag != "1" && flag != "2") {
        std::cerr << "Error: flag must be 1 or 2.\n";
        return 1;
    }

    try {
        // Read and normalize the input file.
        const InputData data = readInputFile(argv[1]);

        // Temporary diagnostic.
        std::cout << "Read " << data.rawTokens
            << " tokens; kept "
            << data.words.size()
            << " normalized words.\n";

        // Initialization of the Standard Trie and BST based Trie

        // Create the two Tries.
        TreeNode standard;
        BSTTrie bst;

        // Standard Trie operation and node counters.
        int std_ops = 1; // Count the empty root node.
        int spc_ops = 0; // Additional nodes created.

        // Builds the standard Trie.
        for (const std::string& word : data.words) {
            insert(word, standard, std_ops, spc_ops);
        }

        // Builds    the BST-based Trie.
        for (const std::string& word : data.words) {
            bst.insert(word);
        }

        // Print construction measurements.
        std::cout << "Number of words: "
            << data.words.size() << '\n';

        std::cout << "Time taken to build the standard Trie is "
            << std_ops << " operations.\n";

        std::cout << "Space occupied by the standard Trie is "
            << (spc_ops + 1) * 26
            << " pointer units.\n";

        std::cout << "Time taken to build the BST based Trie is "
            << bst.getBuildOperations()
            << " operations.\n";

        std::cout << "Space occupied by the BST based Trie is "
            << bst.getPointerUnits()
            << " pointer units.\n";


        // Execute the selected mode.
        if (flag == "1") {
            runQueryMode(standard, bst);
        }
        else {
            runAllWordsMode(data, standard, bst);
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }

    return 0;
}
