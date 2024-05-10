#ifndef MANAGE_USERS_H
#define MANAGE_USERS_H


#include "validations.h"

using std::cout;
using std::cin;
using std::endl;

class Manage_users {
public:
    Manage_users(Program_Data& pd, Input_Validations& iv);

    void Register_user();

    void Remove_user();

    void Update_user();

private:
    Program_Data& pd;
    Input_Validations& iv;
    vector<string> nwlist;
    string nwName;
    string nwRole;
    string nwpassword;
    string search;
};

#endif
