#include "get_a_book.h"


GetBook::GetBook(SearchLibrary& sl, Program_Data& pd, Input_Validations& iv, manage_transactions& mt) : sl(sl), pd(pd), iv(iv), mt(mt) {}


void GetBook::rentaBook() {

    

    string msg = "Enter The ID of the Borrower: ";
    user_id = iv.find_users_id(msg);

    cout << endl;

    rentaBook(user_id);
}

void GetBook::rentaBook(std::string user_id) {
    
    if (pd.Payment_Method.find(user_id) != pd.Payment_Method.end()) {

        string check_Card_Date = pd.Payment_Method[user_id].expiration_date;
        if (iv.VisaDate(check_Card_Date)) {

            string msg = "Find The Book By ID or Title: ";

            search = iv.search_for_a_book(msg);

            if (search != "") {
                int occurence = 0;
                for (const auto& entry : pd.Borrow_details[user_id].Borrowed_Book) {
                    if (entry == search) {
                        occurence += 1;
                    }
                }
                if (occurence == 0) {
                    if (pd.libBooks[search].InStock == 0) {
                        std::cout << endl << "Sorry. This book is not in stock." << std::endl;
                    }
                    else {
                        Borrow_date = iv.formattedDate();
                        if (pd.Borrow_details.find(user_id) == pd.Borrow_details.end()) {
                            pd.Borrow_details.insert({ {user_id}, {{Borrow_date}, {search}} });
                        }
                        else {
                            pd.Borrow_details[user_id].Borrow_date.push_back(Borrow_date);
                            pd.Borrow_details[user_id].Borrowed_Book.push_back(search);
                        }
                        pd.libBooks[search].InStock -= 1;
                        pd.sys_Users[user_id].currentBook.push_back(search);
                        cout << endl << "Book Borrowed Successfully!" << endl << endl;
                        std::cout << "Return the book within 14 days to avoid fees." << std::endl;
                    }
                }
                else {
                    std::cout << "Sorry. You've already borrowed a copy." << std::endl;
                }
            }
            else {
                std::cout << "This does not exist in our library." << std::endl;
            }


        }
        else {

            cout << endl;
            cout << "Payment Method Has Expired." << endl;
            cout << "Add A New Payment Method Now To Continue Borrowing? Yes/No: ";


            choice = iv.yes_or_no();
            cout << endl;

            if (choice == "yes") {

                mt.add_payment_method(user_id);
                rentaBook(user_id);
            }
            else {
                cout << "Returning to dashboard." << endl << endl;
            }
            
        }
    }
    else {
        cout << endl;
        cout << "Account Needs A Payment Method To Borrow." << endl;
        cout << "Add A Payment Method Now? Yes/No: ";


        choice = iv.yes_or_no();
        cout << endl;

        if (choice == "yes") {

            mt.add_payment_method(user_id);
            rentaBook(user_id);
        }
        else {
            cout << "Returning to dashboard." << endl << endl;
        }
    }
    

    
}
