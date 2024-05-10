
#include "search_library.h"

SearchLibrary::SearchLibrary(Program_Data& pd) : pd(pd), presence(0), decision(0) {}

bool SearchLibrary::findBook() {
    cout << "Find Book using the Book ID or Title: ";
    cin >> bkSearch;
    if (libCompare()) {
        return true;
    }
    else {
        return false;
    }
}

bool SearchLibrary::libCompare() {
    for (const auto& pair : pd.libBooks) {
        if ((bkSearch.length() == pair.first.length()) || (bkSearch.length() == pair.second.Title.length())) {
            bool match = true;
            if (match) {
                for (char i : pair.first) {
                    compBkID.push_back(std::tolower(i));
                }
                for (char i : pair.second.Title) {
                    compTitle.push_back(std::tolower(i));
                }
                for (char i : bkSearch) {
                    compInput.push_back(std::tolower(i));
                }

                if (listcomp(compInput, compBkID) || listcomp(compInput, compTitle)) {
                    for (char i : compInput) {
                        bkSearch_lower += i;
                    }
                    bkSearch = bkSearch_lower;
                    return true;
                }
                else {
                    return false;
                }
            }
        }
    }
    return false;
}

bool SearchLibrary::listcomp(vector<char> A, vector<char> B, int indexA, int indexB) {
    if (indexA == A.size() || indexB == B.size())
        return true;
    if (A[indexA] == B[indexB])
        return listcomp(A, B, indexA + 1, indexB + 1);
    else {
        return false;
    }
}

string SearchLibrary::GetInput() {
    return bkSearch;
}
