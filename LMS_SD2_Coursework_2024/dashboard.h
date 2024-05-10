#ifndef DASHBOARD_H
#define DASHBOARD_H

#include "returns.h"
#include "handling.h"
#include "manage_user.h"
#include "manage_books.h"
#include "get_a_book.h"

class Dashboard {
public:
    Dashboard(Program_Data& pd, ManageBooks& mb, Manage_users& mu, GetBook& gb, RetBook& rb, fineCalculator& fc, file_handling& fh, Input_Validations& iv);

    void interface(string user);

    void student_interface(string user);

    void librarian_interface();

    void User_Interaction(int studentchoice, string user);

    void User_Interaction(int adminchoice);

private:
    string userID_fees_chk;
    string userRole;
    int studentchoice = 0;
    int adminchoice = 0;
    int modType = 0;
    float fees = 0.00f;
    ManageBooks& mb;
    Program_Data& pd;
    Manage_users& mu;
    RetBook& rb;
    GetBook& gb;
    fineCalculator& fc;
    file_handling& fh;
    Input_Validations& iv;
 
};

#endif 
