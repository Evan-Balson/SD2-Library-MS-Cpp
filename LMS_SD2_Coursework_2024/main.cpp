/*

SD1 - LMS Coursework
Evan Balson - BAL18466416
Software Development 2 - CMP020C104S
Last Update: 18/04/2024
Coursework:  STEPWISE UNIVERSITY's LIBRARY MANAGEMENT SYSTEM

*/

// Calling all necessary header files
# include "program_data.h"
# include "validations.h"
# include "user_login.h"
# include "manage_user.h"
# include "search_library.h"
# include "manage_books.h"
# include "fines.h"
# include "returns.h"
# include "get_a_book.h"
# include "handling.h"
# include "dashboard.h"
# include "transaction.h"

// Changing the behaviour of the cin to accept stings with spaces
// Defining a structure that inherits from ctype<char> 
struct changeDelimiter : ctype<char> {

    // Constructor for changeDelimiter 
    changeDelimiter()
        : ctype<char>(
            createTable()) // Initializing the base class 
        // ctype<char> with a table 
    {
    }
    // Static function to create a table with custom 
    // settings 
    static mask const* createTable()
    {
        static mask
            rc[table_size]; // Creating a table with the 
        // size of the character set 
        rc['\n']
            = ctype_base::space; // Set the newline 
        // character to be treated 
        // as whitespace 
        return rc; // Return the modified table 
    }
};



int main(int argc, char** argv)
{
    // Creating a custom locale with the changeDelimiter 
    cin.imbue(locale(cin.getloc(), new changeDelimiter));

    int BF_Limit = 1; // Brute force login protection limit to 3 tries.
    int privilege = 0; // Used to identify the user role later.
    string active_user = "NULL"; // Will be used to collect user's Identification.
    string status; // Will be used as a system status indicator later.
    string choice; // Determines the start & stop time for the program.



    cout << "WELCOME TO STEPWISE UNIVERSITY's LIBRARY MS." << endl;
    cout << endl;

    
    // These initialize objects so that we can pass data from the various classes

    Program_Data loading;

    Input_Validations valid(loading);
    UserLogin gotologin(loading);
    Manage_users manage_userdata(loading, valid);
    SearchLibrary search(loading);
    ManageBooks manage(loading, valid);
    manage_transactions bank(loading, valid);
    fineCalculator fines(loading, valid);
    RetBook ret(search, loading, valid, fines,bank);
    GetBook rent(search, loading, valid,bank);
    file_handling files(loading);

    files.file_handling_chk();
    
    // login and identify user details.
    // User has 3 attempts before the program shuts down as brute force protection.
    while ((active_user == "NULL") and (BF_Limit <= 3)) {
        if (BF_Limit > 1) {
            cout << "Incorrect login details. Please Try Again." << endl;
            cout << endl;
        }
        BF_Limit += 1;
        active_user = gotologin.login();
    }
    
    // Deciding whether or not to activate and allow user into the dashboard.
    // Once Logged in the user will be resposibly reminded to log-out after completing tasks.
    if (active_user != "NULL")
    {
        status = "logged In";
        while (status == "logged In") {

            Dashboard layout(loading, manage, manage_userdata, rent, ret, fines, files, valid);
            cout << endl;
            layout.interface(active_user);

            cout << endl;
            cout << "Log-Out? Enter Yes/No: ";
            choice = valid.yes_or_no();

            if (choice == "yes") {
                // Save file states before exiting
                files.update_file();
                files.writeToCSV();
                status = "log-out";
                cout << endl << "Bye! See you soon!" << endl;


            }
            else {
                status = "logged In";
            }

        }
    }
    else
    {
        cout << endl;
        cout << "User not found. Contact a librarian for assistance." << endl;
    }
    

    return 0;

}
