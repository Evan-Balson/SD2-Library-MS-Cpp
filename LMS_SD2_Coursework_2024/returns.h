# ifndef RETURNS
# define RETURNS


# include "validations.h"
# include "fines.h"
# include "search_library.h"
# include "transaction.h"


class RetBook {
public:
    RetBook(SearchLibrary& sl, Program_Data& pd, Input_Validations& iv, fineCalculator& fc, manage_transactions& mt);

    void returnaBook();

    void returnaBook(string user_id);

private:
    SearchLibrary& sl;
    Program_Data& pd;
    Input_Validations& iv;
    fineCalculator& fc;
    manage_transactions& mt;
    string search;
    string user_id;
    string retDate;
    float total_fees=0.0;
    int user_position=0;
    int borrow_position=0;
    bool found=false;
    string transaction;
    string s;
    string msg;
};

#endif
