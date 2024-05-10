#ifndef PROGRAM_DATA_H
#define PROGRAM_DATA_H


# include <iostream>
# include <string>
# include <unordered_map>
# include <vector>
# include <iomanip> // just to help format the outputs
# include <cctype> // Include the cctype header for converting into lower or uppercase
# include <locale> // This changes the behaviour of the cin ~ no more double enter presses.
# include <ctime>
# include <sstream>
# include <algorithm>
# include <fstream> // dealing with files and writting files
# include <regex>


using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::unordered_map;
using std::vector;
using std::setw;

using namespace std;

//These structures link with the program data dictionaries and will allow for better readability
struct UserDetails {
    string user_name;
    string password;
    string role;
    vector <string> currentBook;

};

struct BookDetails {
    string Title;
    vector <string> Authors;
    int Year = 0;
    string Publisher;
    int QTY = 0;
    int InStock = 0;
    vector <string> Subjects;

};

struct booking {
    vector <string> Borrow_date;
    vector <string> Borrowed_Book;


};

struct returnDetails {


    vector <string> return_Date;
    vector <string> returned_Book;
    vector <float> totalFees;
    vector <string> transaction_ID;


};

struct account_pay {

    string card_number;
    string sortcode;
    int pin;
    string expiration_date;


};

// successfully initiallized
class Program_Data {
public:

    // These variables will act as the program counter.
    // It is resposible for features related to the Book & User ID creation.
    int latest_BID = 0;
    int latest_UID = 0;
    int Transaction_IDC = 0;


    // don't forget to update the users current book and set the book staatus to unavailable.
    // don't forget to validate the date format

    unordered_map <string, BookDetails> libBooks;

    unordered_map <string, booking> Borrow_details;

    unordered_map <string, returnDetails> Book_returns;

    unordered_map <string, UserDetails> sys_Users;

    unordered_map< string, account_pay> Payment_Method;

   
};

#endif
