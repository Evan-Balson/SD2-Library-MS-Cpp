#ifndef SEARCH_LIBRARY_H
#define SEARCH_LIBRARY_H

#include <iostream>
#include <string>
#include <vector>
#include "program_data.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

class SearchLibrary {
public:
    SearchLibrary(Program_Data& pd);

    bool findBook();

    bool libCompare();

    bool listcomp(vector<char> A, vector<char> B, int indexA = 0, int indexB = 0);

    string GetInput();

private:
    Program_Data& pd;
    string fbinput;
    string bkSearch;
    string bkSearch_lower;
    int presence;
    vector<char> compInput;
    vector<char> compBkID;
    vector<char> compTitle;
    int decision;
};

#endif /* SEARCH_LIBRARY_H */
