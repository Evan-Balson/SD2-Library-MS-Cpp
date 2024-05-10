#include "handling.h"
#include "demo_data.h"
#include "System_Directory_Scan.h"


    file_handling::file_handling(Program_Data& pd) : pd(pd){}

    // before you run the imoport or create.. check that the file is opened successfully and not interupted
    void file_handling::file_handling_chk() {
        System_Directory_Scan system;


        // create name the new directory for receipts:
        string newDirPath = "program_files";

        // Create the directory
        if (system.createDirectory(newDirPath, fullPath)) {
            //std::cout << "New directory path: " << fullPath << std::endl;
            cout << "" << endl;
        }
    
        try {
            for (int i = 0; i < filenames.size(); i++) {
                file_location = "program_files/" + filenames[i];
                ifstream file(file_location);

                if (!file.is_open()) {
                    missing_files += 1;
                    cerr << "Error: Unable to open file " << filenames[i] << endl << endl;
                }
            }

            if (missing_files > 0) {
                cout << "Some Files Are Missing. Initializing New Data..." << endl << endl;


                create_file(filenames, fullPath);
                insert_demo_data();
                cout << endl << "System data loaded successfully." << endl << endl;
            }
            else {
                cout << "Saved data found. Importing..." << endl << endl;
                import_from_file();
                cout << endl << "System data loaded successfully." << endl << endl;
            }
        }
        catch (const exception& e) {
            cerr << "Exception occurred: " << e.what() << endl << endl;
        }


    }

    void file_handling::import_from_file() {


        for (int i = 0; i < filenames.size(); i++) {


            ifstream file("program_files/" + filenames[i]);
            string line;

            if (file.is_open()) {
                while (getline(file, line)) {
                    //parse line and append to Dictionaries.
                    istringstream iss(line);
                    bool check = false;

                    switch (i) {

                    case 0://return Details
                        iss >> user_ID >> date >> book >> total_Fees >> transaction;

                        im_date.push_back(date);
                        im_book.push_back(book);
                        Fees.push_back(total_Fees);
                        im_transaction.push_back(transaction);


                        if (pd.Book_returns.find(user_ID) != pd.Book_returns.end()) {
                            //append

                            for (const auto& entry : pd.Book_returns[user_ID].returned_Book) {
                                if (entry == book) {
                                    
                                }

                                else {
                                    pd.Book_returns[user_ID].return_Date.push_back(date);
                                    pd.Book_returns[user_ID].returned_Book.push_back(book);
                                    pd.Book_returns[user_ID].totalFees.push_back(total_Fees);
                                    pd.Book_returns[user_ID].transaction_ID.push_back(transaction);
                                }

                            }




                        }
                        else {
                            //insert

                            pd.Book_returns.insert({ {user_ID}, {{im_date},{im_book},{Fees}, {im_transaction}} });

                        }

                        //clear all variables
                        im_date.clear();
                        im_book.clear();
                        im_transaction.clear();
                        Fees.clear();
                        user_ID = "";
                        date = "";
                        book = "";
                        transaction = "";
                        total_Fees = 0.00;


                        break;
                    case 1: // borrow details
                        iss >> user_ID >> date >> book;

                        im_date.push_back(date);
                        im_book.push_back(book);

                        if (pd.Borrow_details.find(user_ID) != pd.Borrow_details.end()) {
                            //
                            for (const auto& entry : pd.Borrow_details[user_ID].Borrowed_Book) {
                                if (entry == book) {
                                    cout << "Borrow details for " << book << "already exists." << endl;
                                }

                                else {
                                    pd.Borrow_details[user_ID].Borrowed_Book.push_back(book);
                                    pd.Borrow_details[user_ID].Borrow_date.push_back(date);
                                }

                            }


                        }
                        else {

                            //insert
                            pd.Borrow_details.insert({ {user_ID}, {{im_date},{im_book}} });


                        }


                        //clear all variables
                        im_date.clear();
                        im_book.clear();
                        user_ID = "";
                        date = "";
                        book = "";

                        break;
                    case 2: // library books

                        iss >> book >> title >> year >> publisher >> QTY >> Stock;

                        std::replace(title.begin(), title.end(), '-', ' ');
                        std::replace(publisher.begin(), publisher.end(), '-', ' ');

                        if (pd.libBooks.find(book) == pd.libBooks.end()) {

                            //insert

                            pd.libBooks.insert({ {book}, {{title},{/*authors*/},{year},{publisher},{QTY},{Stock},{/*subjects*/}} });
                        }


                        //clear all variables
                        book = "";
                        title = "";
                        year = 0;
                        publisher = "";
                        QTY = 0;
                        Stock = 0;


                        break;
                    case 3:// Library_books_authors.txt
                        // format id > vector


                        iss >> book >> author;

                        std::replace(author.begin(), author.end(), '-', ' ');

                        if (pd.libBooks.find(book) != pd.libBooks.end()) {

                            if (pd.libBooks[book].Authors.empty()) {

                                pd.libBooks[book].Authors.push_back(author);
                            }
                            else {

                                for (const auto& entry : pd.libBooks[book].Authors) {
                                    if (entry == author) {
                                        check = true;
                                    }

                                }

                                if (check == false) {
                                    pd.libBooks[book].Authors.push_back(author); // Store the data vector in the map
                                }

                            }

                        }
                        else {
                            cout << "Please check source file." << endl << "Offline Modification Detected For ID:" << book << endl;
                        }

                        //clear all variables
                        im_author.clear();
                        book = "";
                        break;

                    case 4:// Library_books_Tags.txt
                        iss >> book >> subjects;

                        std::replace(subjects.begin(), subjects.end(), '-', ' ');


                        if (pd.libBooks.find(book) != pd.libBooks.end()) {

                            if (pd.libBooks[book].Subjects.empty()) {

                                pd.libBooks[book].Subjects.push_back(subjects);
                            }
                            else {

                                for (const auto& entry : pd.libBooks[book].Subjects) {
                                    if (entry == subjects) {
                                        check = true;
                                    }

                                }

                                if (check == false) {
                                    pd.libBooks[book].Subjects.push_back(subjects); // Store the data vector in the map
                                }

                            }

                        }
                        else {
                            cout << "Please check source file." << endl << "Offline Modification Detected For ID:" << book << endl;
                        }

                        //clear all variables
                        im_subject.clear();
                        book = "";

                        break;

                    case 5:// Registry
                        iss >> user_ID >> fname >> lname >> password >> role;

                        user_name = fname + " " + lname;

                        if (pd.sys_Users.find(user_ID) != pd.sys_Users.end()) {
                            //user exists
                            cout << "A user with ID " << user_ID << "already exists." << endl;


                        }
                        else {

                            //insert
                            pd.sys_Users.insert({ {user_ID}, {{user_name}, {password},{role}, {/*active books*/}} });
                        }


                        user_ID.clear();
                        user_name.clear();
                        fname.clear();
                        lname.clear();
                        password.clear();
                        role.clear();
                        //clear all variables
                        break;

                    case 6:// Users Active Books
                        iss >> user_ID >> book;

                        if (pd.sys_Users.find(user_ID) != pd.sys_Users.end()) {

                            if (pd.sys_Users[user_ID].currentBook.empty()) {

                                pd.sys_Users[user_ID].currentBook.push_back(book);
                            }
                            else {

                                for (const auto& entry : pd.sys_Users[user_ID].currentBook) {
                                    if (entry == book) {
                                        check = true;
                                    }

                                }

                                if (check == false) {
                                    pd.sys_Users[user_ID].currentBook.push_back(book); // Store the data vector in the map
                                }

                            }

                        }
                        else {
                            cout << "Please check source file." << endl << "Offline Modification Detected For ID:" << book << endl;
                        }


                        //clear all variables]
                        book.clear();
                        user_ID = "";

                        break;

                    case 7:
                        // import program count details
                        iss >> book_count >> user_count >> transaction_count;
                        pd.latest_BID = book_count;
                        pd.latest_UID = user_count;
                        pd.Transaction_IDC = transaction_count;



                        break;

                    case 8:

                        iss >> user_ID >> card >> sortcode >> pin >> date;

                        if (pd.Payment_Method.find(user_ID) == pd.Payment_Method.end()) {

                            //insert

                            pd.Payment_Method.insert({ {user_ID}, {{card},{sortcode},{pin},{date}} });
                        }

                        // clear variables after
                        user_ID = "";
                        card = "";
                        sortcode = "";
                        pin = 0;
                        date ="";



                        break;
                    }



                }

            }
            else {
                cout << "Can't open the file." << endl;
            }


            file.close();

        }
    }

    void file_handling::create_file(vector<string>& list, string folder_name) {
        
        for (int i = 0; i < list.size(); i++) {
            string filename = folder_name + "/" + list[i];
            ofstream file(filename);
        }

    }

    // should run only if file already exists.
    void file_handling::update_file() {

        ofstream myfile;



        // write to file
        for (int i = 0; i < filenames.size(); i++) {

            switch (i) {

            case 0:// "return_details.txt",

                myfile.open("program_files/" + filenames[i]);
                for (const auto& entry : pd.Book_returns) {


                    for (int i = 0; i < pd.Book_returns[entry.first].returned_Book.size(); i++) {

                        myfile << entry.first << "\t"
                            << pd.Book_returns[entry.first].return_Date[i] << "\t"
                            << pd.Book_returns[entry.first].returned_Book[i] << "\t"
                            << pd.Book_returns[entry.first].totalFees[i] << "\t"
                            << pd.Book_returns[entry.first].transaction_ID[i] << endl;


                    }




                }

                myfile.close();


                break;


            case 1:
                // "borrow_details.txt"
                // iss >> user_ID >> date >> book;

                myfile.open("program_files/" + filenames[i]);
                for (const auto& entry : pd.Borrow_details) {


                    for (int i = 0; i < pd.Borrow_details[entry.first].Borrowed_Book.size(); i++) {

                        myfile << entry.first << "\t"
                            << pd.Borrow_details[entry.first].Borrow_date[i] << "\t"
                            << pd.Borrow_details[entry.first].Borrowed_Book[i] << endl;


                    }



                }

                myfile.close();


                break;


            case 2: //"Library_books.txt",
                // iss >> book >> title >> year >> publisher >> QTY >> Stock;

                myfile.open("program_files/" + filenames[i]);
                for (const auto& entry : pd.libBooks) {

                    string t = entry.second.Title;
                    string p = entry.second.Publisher;
                    std::replace(t.begin(), t.end(), ' ', '-');
                    std::replace(p.begin(), p.end(), ' ', '-');

                    myfile << entry.first << "\t"
                        << t << "\t"
                        << entry.second.Year << "\t"
                        << p << "\t"
                        << entry.second.QTY << "\t"
                        << entry.second.InStock << endl;


                }


                myfile.close();


                break;


            case 3: // Library_books_authors.txt
                // format id > vector

                myfile.open("program_files/" + filenames[i]);
                for (const auto& entry : pd.libBooks) {


                    for (int i = 0; i < pd.libBooks[entry.first].Authors.size(); i++) {

                        string p = pd.libBooks[entry.first].Authors[i];
                        std::replace(p.begin(), p.end(), ' ', '-');

                        myfile << entry.first << "\t"
                            << p << endl;


                    }


                }

                myfile.close();

                break;


            case 4: // "Library_books_Tags.txt This is the subjects
                // format id > vector

                myfile.open("program_files/" + filenames[i]);
                for (const auto& entry : pd.libBooks) {


                    for (int i = 0; i < pd.libBooks[entry.first].Subjects.size(); i++) {

                        string p = pd.libBooks[entry.first].Subjects[i];
                        std::replace(p.begin(), p.end(), ' ', '-');

                        myfile << entry.first << "\t"
                            << p << endl;


                    }


                }

                myfile.close();

                break;


            case 5: //  "registry.txt",
                // iss >> user_ID >> password >> role;

                myfile.open("program_files/" + filenames[i]);
                for (const auto& entry : pd.sys_Users) {

                    string fname;
                    string lname;


                    size_t spaceIndex = entry.second.user_name.find(' ');
                    if (spaceIndex == string::npos) {
                        cerr << "Error: Invalid input. Full name must contain both first and last names separated by a space." << endl;
                    }
                    else {
                        string firstName = entry.second.user_name.substr(0, spaceIndex);
                        string lastName = entry.second.user_name.substr(spaceIndex + 1);


                        myfile << entry.first << "\t"
                            << firstName << "\t"
                            << lastName << "\t"
                            << entry.second.password << "\t"
                            << entry.second.role << endl;
                    }

                }


                myfile.close();


                break;


            case 6: // "user_active_books.txt",
                // format id > vector


                myfile.open("program_files/" + filenames[i]);
                for (const auto& entry : pd.sys_Users) {


                    for (int i = 0; i < pd.sys_Users[entry.first].currentBook.size(); i++) {


                        myfile << entry.first << "\t"
                            << pd.sys_Users[entry.first].currentBook[i] << endl;



                    }


                }


                myfile.close();

                break;


            case 7: // "program_counter"
                // use pd directly

                myfile.open("program_files/" + filenames[i]);

                myfile << pd.latest_BID << "\t"
                    << pd.latest_UID << "\t"
                    << pd.Transaction_IDC << endl;


                myfile.close();


                break;

            case 8:
                // update payment methods

                myfile.open("program_files/" + filenames[i]);
                for (const auto& entry : pd.Payment_Method) {
                                       
                    myfile << entry.first << "\t"
                        << entry.second.card_number << "\t"
                        << entry.second.sortcode << "\t"
                        << entry.second.pin << "\t"
                        << entry.second.expiration_date << endl;


                }


                myfile.close();

                break;
            }


        }


    }

    void file_handling::insert_demo_data() {
        // Create an instance of ini_Program_Data to access the initial data
        ini_Program_Data initial_data;

        // Update the program data with the demo data
        pd.latest_BID = initial_data.ini_latest_BID;
        pd.latest_UID = initial_data.ini_latest_UID;
        pd.Transaction_IDC = initial_data.Transaction_IDC;
        pd.sys_Users = initial_data.ini_sys_Users;
        pd.libBooks = initial_data.ini_libBooks;
        pd.Borrow_details = initial_data.ini_Borrow_details;
        pd.Book_returns = initial_data.ini_Book_returns;
        pd.Payment_Method = initial_data.ini_Payment_Method;

        update_file();
    }



    // this function helps on import to separate the Id from the vector list
    vector<string> file_handling::split(const string& s, char delimiter) {
        vector<string> tokens;
        stringstream ss(s);
        string token;
        while (getline(ss, token, delimiter)) {
            tokens.push_back(token);
        }
        return tokens;
    }


    void file_handling::writeToCSV() {
        //initializing system object

        System_Directory_Scan system;


        // create name the new directory for receipts:
        string newDirPath = "storage";

        // Create the directory
        if (system.createDirectory(newDirPath, fullPath)) {

            cout << "" << endl;
            //std::cout << "New directory path: " << fullPath << std::endl;
        }

        
        try{

            for (int i = 0; i < csv_filenames.size(); i++) {
                write_path = "storage/" + csv_filenames[i];

                ifstream file(write_path);
                if (!file.is_open()) {
                    missing_files += 1;
                    cerr << "Error: Unable to open file " << csv_filenames[i] << endl;
                }
            }

            if (missing_files > 0) {
                cout << endl << "Missing files detected. creating New Data..." << endl;
                
                create_file(csv_filenames, newDirPath);
                missing_files = 0;
                writeToCSV();
                cout << endl << "csv created successfully." << endl << endl;
            }
            else {
                cout << endl << "csv files found. updating..." << endl;
                // Library books
                library_books_spreadsheet();
                // Borrowed books
                borrow_details_spreadsheet();
                // Returns
                returns_spreadsheet();
                // Fines & Transaction ID
                transactions_spreadsheet();
            }
        }
        catch (const exception& e) {
            cerr << "Exception occurred: " << e.what() << endl;
        }
    
    }

    void file_handling::library_books_spreadsheet() {

                
        ofstream outFile("storage/library_books.csv");

        if (!outFile) {
            cerr << "Error: Unable to open file 'library_books.csv' for writing." << endl;
            return;
        }

        // Write the header row
        outFile << "Title,Authors,Year,Publisher,QTY,InStock,Subjects" << endl;

        // Iterate through the book details map
        for (const auto& entry : pd.libBooks) {
            // Write each book detail entry to the CSV file
            outFile << entry.second.Title << ",";

            // Write authors (comma-separated)
            for (size_t i = 0; i < entry.second.Authors.size(); ++i) {
                outFile << entry.second.Authors[i];
                if (i < entry.second.Authors.size() - 1) {
                    outFile << ";"; // Use semicolon as author separator
                }
            }
            outFile << "," << entry.second.Year << ","
                << entry.second.Publisher << ","
                << entry.second.QTY << ","
                << entry.second.InStock << ",";

            // Write subjects (comma-separated)
            for (size_t i = 0; i < entry.second.Subjects.size(); ++i) {
                outFile << entry.second.Subjects[i];
                if (i < entry.second.Subjects.size() - 1) {
                    outFile << ";"; // Use semicolon as subject separator
                }
            }
            outFile << endl;
        }

        // Close the file
        outFile.close();

             
    }

    void file_handling::returns_spreadsheet() {
        ofstream outFile("storage/returns.csv");

        if (!outFile) {
            cerr << "Error: Unable to open file 'returns.csv' for writing." << endl;
            return;
        }

        // Write the header row
        outFile << "return_Date,returned_Book,transaction_ID" << endl;

        // Iterate through the return details map
        for (const auto& entry : pd.Book_returns) {
            // Write each return detail entry to the CSV file
            for (size_t i = 0; i < entry.second.return_Date.size(); ++i) {
                outFile << entry.second.return_Date[i] << ","
                    << entry.second.returned_Book[i] << ","
                    << entry.second.transaction_ID[i] << endl;
            }
        }

        // Close the file
        outFile.close();
    }

    void file_handling::borrow_details_spreadsheet() {
    
        ofstream outFile("storage/borrowed_books.csv");

        if (!outFile) {
            cerr << "Error: Unable to open file 'borrowings.csv' for writing." << endl;
            return;
        }

        // Write the header row
        outFile << "User_ID,Borrow_date,Borrowed_Book" << endl;

        // Iterate through the borrowing details map
        for (const auto& entry : pd.Borrow_details) {
            // Write each borrowing detail entry to the CSV file
            const string& userID = entry.first;
            for (size_t i = 0; i < entry.second.Borrow_date.size(); ++i) {
                outFile << userID << "," << entry.second.Borrow_date[i] << ","
                    << entry.second.Borrowed_Book[i] << endl;
            }
        }

        // Close the file
        outFile.close();
    
    }

    void file_handling::transactions_spreadsheet() {
    
        ofstream outFile("storage/fines.csv");

        if (!outFile) {
            cerr << "Error: Unable to open file 'returns.csv' for writing." << endl;
            return;
        }

        // Write the header row
        outFile << "return_Date,totalFees,transaction_ID" << endl;

        // Iterate through the return details map
        for (const auto& entry : pd.Book_returns) {
            // Write each return detail entry to the CSV file
            for (size_t i = 0; i < entry.second.return_Date.size(); ++i) {
                outFile << entry.second.return_Date[i] << ","
                    << entry.second.totalFees[i] << ","
                    << entry.second.transaction_ID[i] << endl;
            }
        }

        // Close the file
        outFile.close();
    
    }