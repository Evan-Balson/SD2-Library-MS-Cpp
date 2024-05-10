#include "returns.h"
#include "transaction.h"

RetBook::RetBook(SearchLibrary& sl, Program_Data& pd, Input_Validations& iv, fineCalculator& fc, manage_transactions& mt) : sl(sl), pd(pd), iv(iv), fc(fc), mt(mt) {}

void RetBook::returnaBook() {
    msg = "Enter The ID of the Borrower: ";
    user_id = iv.find_users_id(msg);

    cout << endl;

    returnaBook(user_id);
}

void RetBook::returnaBook(string user_id) {
    
    string msg = "Enter The Book Title or ID For This Return: ";
    search = iv.search_for_a_book(msg);
    cout << endl;

    if (search != "") {
        if (std::find(pd.sys_Users[user_id].currentBook.begin(), pd.sys_Users[user_id].currentBook.end(), search) != pd.sys_Users[user_id].currentBook.end()) {
            retDate = iv.formattedDate();
            total_fees = fc.calculate_fines(user_id, retDate, search);

            if (total_fees == 0) {
                transaction = mt.process_payment(user_id, total_fees, search);
                cout << "Hurray! No charges have been applied." << endl;


            }
            else {
                cout << "You're late. $" << total_fees << " will be charged to your account." << endl;

                cout << "Processing Payment..." << endl << endl;
                transaction = mt.process_payment(user_id, total_fees, search);
                
            }

            if (transaction == "failed") {
                cout << endl << endl << "Please register a payment method soon to avoid accrued fees." << endl;
            }
            
            else {

                if (pd.Book_returns.find(user_id) == pd.Book_returns.end()) {
                    pd.Book_returns.insert({ {user_id}, {{retDate}, {search}, {total_fees}, {transaction}} });
                }
                else {
                    pd.Book_returns[user_id].return_Date.push_back(retDate);
                    pd.Book_returns[user_id].returned_Book.push_back(search);
                    pd.Book_returns[user_id].totalFees.push_back(total_fees);
                    pd.Book_returns[user_id].transaction_ID.push_back(transaction);
                }

                for (int i = 0; i < pd.sys_Users[user_id].currentBook.size(); i++) {
                    if (search == pd.sys_Users[user_id].currentBook[i]) {
                        user_position = i;
                        break;
                    }
                }

                for (int i = 0; i < pd.Borrow_details[user_id].Borrowed_Book.size(); i++) {
                    if (search == pd.Borrow_details[user_id].Borrowed_Book[i]) {
                        borrow_position = i;
                        break;
                    }
                }

                pd.Borrow_details[user_id].Borrowed_Book.erase(pd.Borrow_details[user_id].Borrowed_Book.begin() + borrow_position);
                pd.Borrow_details[user_id].Borrow_date.erase(pd.Borrow_details[user_id].Borrow_date.begin() + borrow_position);
                pd.sys_Users[user_id].currentBook.erase(pd.sys_Users[user_id].currentBook.begin() + user_position);
                pd.libBooks[search].InStock += 1;
            }
        }
        else {
            cout << "Sorry. This book could not be found in your owned collection." << endl;
        }
    }
    else {
        cout << "Sorry. This book does not exist in our library." << endl;
    }
}
