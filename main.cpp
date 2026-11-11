
#include "input.hpp"
#include "stdtrie.hpp"

#include <exception>
#include <iostream>
#include <string>

// Flag 1: accept queries until EOF or Ctrl-C.
void runQueryMode() {
    std::string rawQuery;

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
        std::cout << "Normalized query: " << query << '\n';

        // TODO: Search standard Trie.
        // TODO: Display standard Trie autocomplete results.
        // TODO: Print standard Trie operation counts.

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
        //standard.value = false;

        std::string w = data.words[2];

        insert(w, standard);

        std::cout << "does 'is' exist? " << standard.child[8]->child[18]->value << "\n";

        //std::cout << "value of index 4: " << standard.child[0]->value << "\n";
        /*
        w.erase(w.begin());
        std::cout << "word after erasing: " << w << "\n";
        int l = w.length();
        std::cout << "length after erasing: " << l << "\n";

        

        if (standard.value == false)
            std::cout << standard.value << "\n";
        
        if (standard.child[0] == NULL)
            std::cout << "before: there's nothing there!\n";

        TreeNode* child;
        child->value = true;
        standard.child[0] = child;

        if (standard.child[0] == NULL)
            std::cout << "after: there's nothing there!\n";

        

        std::cout << standard.child[0]->value << "\n";
        */
         



        // TODO: Insert every word into BOTH Tries.
        // TODO: Report construction operation counts.
        // TODO: Report space in pointer units.

        // Execute the selected mode.
        if (flag == "1") {
            runQueryMode();
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
