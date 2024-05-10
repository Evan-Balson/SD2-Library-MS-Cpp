#include "user_login.h"

// Constructor definition
UserLogin::UserLogin(Program_Data& pd) : pd(pd) {}

// Definition of the login() member function
string UserLogin::login() {
    std::cout << "Enter Your ID number: ";
    std::cin >> userID;
    std::cout << std::endl;

    if (pd.sys_Users.find(userID) != pd.sys_Users.end()) {
        string msg = "Enter Your password to login: ";
        password = getPassword(msg);
        std::cout << std::endl;


        if (password == pd.sys_Users[userID].password) {
            return userID;
        }
        else {
            return "NULL";
        }
    }
    else {
        return "NULL";
    }
}


string UserLogin::getPassword(string msg) {
    string password;
    char ch;

    cout << msg;

    // Loop until Enter key is pressed
    while (true) {
        ch = _getch(); // Read a character from the console (Windows)
        // ch = getch(); // For Unix systems

        // If Enter key is pressed, break the loop
        if (ch == '\r') {
            break;
        }
        // If Backspace key is pressed, remove the last character from the password
        else if (ch == '\b') {
            if (!password.empty()) {
                cout << "\b \b"; // Move cursor back, overwrite the character with a space, move cursor back again
                password.pop_back(); // Remove the last character from the password
            }
        }
        // If any other character is pressed, add it to the password and print '*'
        else {
            password.push_back(ch); // Add the character to the password
            cout << '*'; // Print '*' to the console
        }
    }

    cout << endl; // Move to the next line

    return password;
}