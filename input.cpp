
#include "input.hpp"

#include <fstream>
#include <stdexcept>
#include <utility>

std::string normalizeWord(const std::string& token) {
    std::string word;
    word.reserve(token.size());

    for (unsigned char c : token) {
        if (c >= 'A' && c <= 'Z') {
            word.push_back(static_cast<char>(c - 'A' + 'a'));
        }
        else if (c >= 'a' && c <= 'z') {
            word.push_back(static_cast<char>(c));
        }
        // Ignore punctuation, digits, and other characters.
    }

    return word;
}

InputData readInputFile(const std::string& filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error(
            "Cannot open input file: " + filename
        );
    }

    InputData data;
    std::string token;

    while (file >> token) {
        ++data.rawTokens;

        std::string word = normalizeWord(token);

        if (!word.empty()) {
            data.words.push_back(std::move(word));
        }
    }

    if (file.bad()) {
        throw std::runtime_error(
            "Error while reading input file: " + filename
        );
    }

    return data;
}
