#ifndef USER_LOGIN_H
#define USER_LOGIN_H

#include "program_data.h"
#include <conio.h>

class UserLogin {
public:
    // Constructor
    UserLogin(Program_Data& pd);

    // Member function for user login
    string login();
    string getPassword(string msg);

private:
    std::string userID;
    std::string password;
    Program_Data& pd;
};

#endif // USER_LOGIN_H
