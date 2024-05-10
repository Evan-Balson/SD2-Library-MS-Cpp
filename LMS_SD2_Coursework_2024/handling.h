#ifndef FILE_HANDLING_H
#define FILE_HANDLING_H

# include "program_data.h"
# include "demo_data.h"


// Assuming Program_Data is defined elsewhere

class file_handling {
public:
    file_handling(Program_Data& pd);

    void file_handling_chk();
    void import_from_file();
    void create_file(vector<string>& list, string full_path);
    void update_file();
    void insert_demo_data();

    void writeToCSV();
    void library_books_spreadsheet();
    void returns_spreadsheet();
    void borrow_details_spreadsheet();
    void transactions_spreadsheet();

    std::vector<std::string> split(const std::string& s, char delimiter);

private:
    vector <string> filenames = { "return_details.txt",
                            "borrow_details.txt",
                            "Library_books.txt",
                            "Library_books_authors.txt",
                            "Library_books_Tags.txt",
                            "registry.txt",
                            "user_active_books.txt",
                            "program_counter.txt",
                            "user_payment_information.txt"};

    vector <string> csv_filenames = {"borrowed_books.csv",
                                    "library_books.csv",
                                    "returns.csv",
                                    "fines.csv"};


    Program_Data& pd;
    string user_ID;
    string date;
    string book;

    float total_Fees = 0.00;
    vector <string> im_date;
    vector <string> im_book;

    vector <float> Fees;

    int year = 0;
    string title;
    string publisher;
    int QTY = 0;
    int Stock = 0;
    string author;
    string subjects;
    vector <string> im_author;
    vector <string> im_subject;

    string user_name;
    string password;
    string role;

    int book_count = 0;
    int user_count = 0;
    string fname;
    string lname;

    int missing_files = 0;
    string transaction;
    vector <string> im_transaction;
    int transaction_count = 0;

    string card;
    string sortcode;
    int pin = 0;

    string write_path;
    string file_location;
    string fullPath;
};

#endif 
