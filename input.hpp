#pragma once
#ifndef INPUT_HPP
#define INPUT_HPP

#include <cstddef>
#include <string>
#include <vector>
using namespace std;

struct InputData {
    vector<string> words;
    size_t rawTokens = 0;
};
string normalizeWord(const string& token);
 
InputData readInputFile(const string& filename);

#endif
