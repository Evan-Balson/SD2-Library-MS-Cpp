#include "Dashboard.h"

Dashboard::Dashboard(Program_Data& pd, ManageBooks& mb, Manage_users& mu, GetBook& gb, RetBook& rb, fineCalculator& fc, file_handling& fh, Input_Validations& iv)
    : pd(pd), mb(mb), mu(mu), gb(gb), rb(rb), fc(fc), fh(fh), iv(iv){}


    void Dashboard::interface(string user) {
        userRole = pd.sys_Users[user].role;
        //cout << "the user role entered in dashboard is " << userRole << endl;

        if (userRole == "student")
        {
            student_interface(user);
        }
        else
        {
            librarian_interface();

        }
    }

    void Dashboard::student_interface(string user) {
        cout << "Welcome To The Student Portal" << endl;
        cout << endl;
        cout << "MAIN MENU:" << endl;
        cout << "1. Borrow or Return A Book." << endl;
        cout << "2. Research A Books Availability" << endl;
        cout << "3. View Account Charges." << endl;
        cout << "4. Exit" << endl;
        cout << endl;
        cout << "Enter a number from the menu above to start: ";
        while (!(cin >> studentchoice) || ((studentchoice > 4) || (studentchoice < 1)))
        {
            cout << endl;
            cout << "Invalid. Enter an integer from 1 - 4: ";
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        }
        User_Interaction(studentchoice, user);
        //cout << "Student Chose option " << studentchoice << endl;

    }

    void Dashboard::librarian_interface() {
        cout << "Welcome To The Library Admin Portal." << endl;
        cout << endl;
        cout << "MAIN MENU:" << endl;
        cout << "1. Register, Update or Delete A Book." << endl;
        cout << "2. Register, Update or Delete A User." << endl;
        cout << "3. Record A Rental or Return." << endl;
        cout << "4. Research Books or Availability." << endl;
        cout << "5. View Borrow Or Return History." << endl;
        cout << "6. Find user fees." << endl;
        cout << "7. Exit" << endl;
        cout << endl;
        cout << "Enter a number from the menu above to start: ";
        while (!(cin >> adminchoice) || ((adminchoice > 7) || (adminchoice < 1)))
        {
            cout << endl;
            cout << "Invalid. Enter an integer from 1 - 7: ";
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        }
        User_Interaction(adminchoice);
        //cout << "Admin Chose option " << adminchoice << endl;
    }

    void Dashboard::User_Interaction(int studentchoice, string user) {

        switch (studentchoice) {
        case 1:
            // Borrow or Return A Book.
            cout << "" << endl;
            cout << "Enter 1 to borrow or 2 to return a book: ";
            while (!(cin >> modType) || ((modType > 2) || (modType < 1)))
            {
                cout << endl << "Invalid. Enter an integer from 1 - 2: ";
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            cout << endl;
            switch (modType) {
            case 1:
                // Borrow
                gb.rentaBook(user);
                fh.update_file();
                break;
            case 2:
                // Return
                rb.returnaBook(user);
                fh.update_file();
                break;

            }

            break;
        case 2:
            // Research Books or Availability
            cout << "" << endl;
            cout << "Here are all books and its availability at the library:" << endl;

            ///////////////////
            cout << endl;
            cout << setw(5) << "";
            cout << left << setw(5) << "QTY";
            cout << setw(5) << "";
            cout << left << setw(8) << "Book ID";
            cout << setw(9) << "";
            cout << left << setw(11) << "Title";
            cout << endl;

            cout << setw(5) << "";
            cout << left << setw(5) << "____";
            cout << setw(5) << "";
            cout << left << setw(8) << "________";
            cout << setw(9) << "";
            cout << left << setw(11) << "______";
            cout << endl;


            for (const auto& pair : pd.libBooks) {
                cout << setw(5) << "";
                cout << left << setw(5) << pair.second.InStock;
                cout << setw(5) << "";
                cout << left << setw(8) << pair.first;
                cout << setw(5) << "";
                cout << left << setw(11) << pair.second.Title;
                cout << endl;

            }
            cout << endl;
            break;
        case 3:
            // Show My Balance.
            cout << "" << endl;
            fees = fc.find_user_fines(user);
            fh.update_file();
            if (fees == 0) { cout << "Congratulations! You Account has No Pending Fees!" << endl << endl; }
            else { cout << "Your Account Has A Pending Balance of $" << fees << " For Late Returns" << endl;
            cout << "Return over-kept books soon to avoid further fees." << endl<< endl; }


            break;
        case 4:
            // Exit

            break;
        }

    }


    void Dashboard::User_Interaction(int adminchoice) {

        switch (adminchoice) {

        case 1:
            // Register, Update or Delete A Book.
            cout << "" << endl;
            cout << "MANAGE THE LIBRARY'S BOOKS:" << endl << endl;
            cout << "1. Register A New Book." << endl;
            cout << "2. Update An Existing Book Details." << endl;
            cout << "3. Delete A Book." << endl << endl;
            cout << "Enter a number from the menu above: ";
            while (!(cin >> modType) || ((modType > 3) || (modType < 1)))
            {
                cout << endl << "Invalid. Enter an integer from 1 - 3: ";
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            switch (modType) {
            case 1:
                // Register
                mb.Register_book();
                fh.update_file();
                break;
            case 2:
                // Update
                mb.Update_book();
                fh.update_file();
                break;
            case 3:
                // Delete
                mb.Delete_book();
                fh.update_file();
                break;

            }

            break;
        case 2:
            // Register, Update or Delete A User.
            cout << endl;
            cout << "MANAGE THE LIBRARY'S USERS:" << endl << endl;
            cout << "1. Register A New User." << endl;
            cout << "2. Update An Existing User Details." << endl;
            cout << "3. Delete A User." << endl << endl;
            cout << "Enter a number from the menu above: ";
            while (!(cin >> modType) || ((modType > 3) || (modType < 1)))
            {
                cout << endl << "Invalid. Enter an integer from 1 - 3: ";
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            cout << endl;
            switch (modType) {
            case 1:
                // Register
                mu.Register_user();
                fh.update_file();
                break;
            case 2:
                // Update
                mu.Update_user();
                fh.update_file();
                break;
            case 3:
                // Delete
                mu.Remove_user();
                fh.update_file();
                break;

            }

            break;
        case 3:
            // Record A Rental or Return.
            cout << endl;
            cout << "MANAGE THE LIBRARY'S BOOKING:" << endl << endl;
            cout << "1. Record A New Rental." << endl;
            cout << "2. Record A Return." << endl << endl;
            cout << "Enter a number from the menu above: ";
            while (!(cin >> modType) || ((modType > 2) || (modType < 1)))
            {
                cout << endl << "Invalid. Enter an integer from 1 - 2: ";
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            cout << endl;
            switch (modType) {
            case 1:
                // Borrow
                gb.rentaBook();
                fh.update_file();

                break;
            case 2:
                // Return
                rb.returnaBook();
                fh.update_file();
                break;

            }

            break;
        case 4:
            // Research Books or Availability.
            cout << "" << endl;
            cout << "Now Viewing Availability For Library Books:" << endl << endl;

            ////////////////
            cout << endl;
            cout << setw(5) << "";
            cout << left << setw(5) << "QTY";
            cout << setw(5) << "";
            cout << left << setw(8) << "Book ID";
            cout << setw(9) << "";
            cout << left << setw(11) << "Title";
            cout << endl;

            cout << setw(5) << "";
            cout << left << setw(5) << "____";
            cout << setw(5) << "";
            cout << left << setw(8) << "________";
            cout << setw(9) << "";
            cout << left << setw(11) << "______";
            cout << endl;


            for (const auto& pair : pd.libBooks) {
                cout << setw(5) << "";
                cout << left << setw(5) << pair.second.InStock;
                cout << setw(5) << "";
                cout << left << setw(8) << pair.first;
                cout << setw(5) << "";
                cout << left << setw(11) << pair.second.Title;
                cout << endl;

            }
            cout << endl;

            break;
        case 5: // Borrow and return history
            cout << endl;
            cout << "1. View Borrow History." << endl;
            cout << "2. View Return History." << endl << endl;
            cout << "Please enter a number from the menu above: ";
            while (!(cin >> modType) || ((modType > 2) || (modType < 1)))
            {
                cout << endl << "Invalid. Enter an integer from 1 - 2: ";
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            cout << endl;

            switch (modType) {
            case 1:
                // Borrow History
                cout << "Borrow History:" << endl << endl;
                cout << setw(20) << left << "User ID" << setw(20) << left << "Borrow Date" << setw(20) << left << "Borrowed Book" << endl;
                cout << "------------------------------------------------------------" << endl;
                for (const auto& entry : pd.Borrow_details) {
                    const string& user_id = entry.first;
                    const booking& details = entry.second;
                    for (size_t i = 0; i < details.Borrow_date.size(); ++i) {
                        cout << setw(20) << left << user_id << setw(20) << left << details.Borrow_date[i] << setw(20) << left << details.Borrowed_Book[i] << endl;
                    }
                }
                cout << endl;


                break;
            case 2:
                // Return History

                cout << "Return History:" << endl << endl;
                cout << setw(20) << left << "User ID" << setw(20) << left << "Return Date" << setw(20) << left << "Returned Book" << setw(20) << left << "Total Fees" << setw(20) << left << "Transaction ID" << endl;
                cout << "-----------------------------------------------------------------------------------------------------------------" << endl;
                for (const auto& entry : pd.Book_returns) {
                    const string& user_id = entry.first;
                    const returnDetails& details = entry.second;
                    for (size_t i = 0; i < details.return_Date.size(); ++i) {
                        cout << setw(20) << left << user_id << setw(20) << left << details.return_Date[i] << setw(20) << left << details.returned_Book[i] << setw(20) << left << details.totalFees[i] << setw(20) << left << details.transaction_ID[i] << endl;
                    }
                }
                cout << endl;


                break;

            }

            break;

           
        

        case 6:
            // Show users Balance.
            cout << "" << endl;

            cout << "Enter a user's ID to view their fees: ";
            cin >> userID_fees_chk;

            while ((pd.sys_Users.find(userID_fees_chk) == pd.sys_Users.end())) {

                cout << endl << endl << "Invalid user ID. please try again: ";
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize> :: max(), '\n');
                cin >> userID_fees_chk;


            
            
            }

            fees = fc.find_user_fines(userID_fees_chk);
            cout << endl;
            if (fees == 0) { cout << "Congratulations! You Account has No Pending Fees!" << endl << endl; }
            else {
                cout << pd.sys_Users[userID_fees_chk].user_name << " 's Account Has A Pending Balance of $" << fees << " For Late Returns" << endl;
                cout << "Advice: Return over-kept books soon to avoid further fees." << endl << endl;
            }


        case 7:
            // Exit
            
            break;
        }

    }
