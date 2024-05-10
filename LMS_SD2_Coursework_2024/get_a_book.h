#ifndef GET_BOOK_H
#define GET_BOOK_H

# include "search_library.h"
# include "validations.h"
# include "transaction.h"

class GetBook {
public:
    GetBook(SearchLibrary& sl, Program_Data& pd, Input_Validations& iv, manage_transactions& mt);

    void rentaBook();
    void rentaBook(std::string user_id);

private:
    SearchLibrary& sl;
    Program_Data& pd;
    manage_transactions& mt;
    Input_Validations& iv;
    std::string search;
    std::string user_id;
    std::string Borrow_date;
    string found = "";
    string choice;
};

#endif /* GET_BOOK_H */
