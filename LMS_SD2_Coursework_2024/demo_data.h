#ifndef DEMO_DATA_H
#define DEMO_DATA_H

#include "program_data.h"

// successfully initialized
class ini_Program_Data {
public:
    int ini_latest_BID = 7276;
    int ini_latest_UID = 1000001;
    int Transaction_IDC = 224;

    unordered_map<string, UserDetails> ini_sys_Users = {
        { "LEE1000001", {"Lee Wei", "password", "librarian", {"7275MATH2024"}} },
        { "EVA1000000", {"Evan Balson", "password", "student", {"7275MATH2024", "7276SSCI2024"}} }
    };

    unordered_map<string, BookDetails> ini_libBooks = {
        { "7275MATH2024", {"Statistics", {"Oscar Levin"}, 2022,
                            "School of Mathematical Science University of Northern Colorado", 20, 18, {"Mathematics", "Number theory"}} },
        { "7274STAT2024", {"Statistics", {"Oscar Levin"}, 2022,
                            "School of Mathematical Science University of Northern Colorado", 1, 1, {"Mathematics"}} },
        { "7276SSCI2024", {"Astro-Physics", {"Carol Henly"}, 2021,
                            "School of Science Oxford University", 13, 12, {"Physics"}} }
    };

    unordered_map<string, booking> ini_Borrow_details = {
        { "EVA1000000", {{"01/02/2024", "29/04/2024"}, {"7275MATH2024", "7276SSCI2024"}} },
        { "LEE1000001", {{"10/03/2024"}, {"7275MATH2024"}} }
    };

    unordered_map<string, returnDetails> ini_Book_returns = {
        { "EVA1000000", {{"01/05/2024", "2024/05/05"}, {"7275MATH2024", "7276SSCI2024"}, {10.00, 12.00}, {"UK-BANK-421", "UK-BANK-422"}} },
        { "LEE1000001", {{"15/04/2024"}, {"7275MATH2024"}, {8.00}, {"UK-BANK-423"}} }
    };

    unordered_map< string, account_pay> ini_Payment_Method = {
        {"EVA1000000", {{"2442-4224-1224-2115"},{"275332"},{555},{"03/23"} }},
        {"LEE1000001", {{"3553-5224-5215-2423"},{"200332"},{333},{"07/27"} }}
    
    
    };
};

#endif
