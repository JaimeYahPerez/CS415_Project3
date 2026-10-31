#ifndef INPUT_HPP
#define INPUT_HPP

#include <cstddef>
#include <string>
#include <vector>

struct InputData {
    std::vector<std::string> words;
    std::size_t rawTokens = 0;
};

std::string normalizeWord(const std::string& token);

InputData readInputFile(const std::string& filename);

#endif
