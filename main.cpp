
#include "input.hpp"
#include "stdtrie.hpp"

#include <exception>
#include <iostream>
#include <string>

// Flag 1: accept queries until EOF or Ctrl-C.
void runQueryMode(TreeNode& trie) {
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

        // Temporary debug output.
        //std::cout << "Normalized query: " << query << '\n';

        // TODO: Search standard Trie.
        search(query, trie, search_ops_trie);
        std::cout << "Time taken to search in the standard Trie is " << search_ops_trie << " operations.\n";
        search_ops_trie = 0; // reset for next while loop
        
        // TODO: Display standard Trie autocomplete results.
        // TODO: Print standard Trie operation counts.
        autocomplete(query, &trie, autocomplete_ops_trie);
        std::cout<< "Time taken to find auto-complete results in the standard Trie is " << autocomplete_ops_trie << " opertions.\n";
        autocomplete_ops_trie = 0; // reset for next loop
       

        // TODO: Search BST-based Trie.
        // TODO: Display BST-based Trie autocomplete results.
        // TODO: Print BST-based Trie operation counts.
    }
}

// Flag 2: search every word from the input file.
void runAllWordsMode(const InputData& data) {

    // Temporary diagnostic.
    std::cout << "Words to search: "
        << data.words.size() << '\n';

    // TODO: Search every word in the standard Trie.
    // TODO: Accumulate standard Trie search operations.

    // TODO: Search every word in the BST-based Trie.
    // TODO: Accumulate BST-based Trie search operations.

    // Do NOT compute autocomplete results for flag 2.
}

int main(int argc, char* argv[]) {
    std::cout << "hello?" << "\n";
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

        // TODO: Create both Trie objects.

        TreeNode standard;
        // TreeNode bst;


        int std_ops = 1; // Root construction
        int spc_ops = 0; // Additional nodes

        for (const std::string& word : data.words) {
            insert(word, standard, std_ops, spc_ops);
        }

        std::cout << "Time taken to build the standard Trie is " << std_ops << " operations.\n";

        std::cout << "Space occupied by it is " << (spc_ops + 1) * 26 << " pointer units.\n";

        // Execute the selected mode.
        if (flag == "1") {
            runQueryMode(standard);
        }
        else {
            runAllWordsMode(data);
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }

    return 0;
}
