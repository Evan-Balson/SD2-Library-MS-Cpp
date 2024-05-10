
#include "fines.h"

fineCalculator::fineCalculator(Program_Data& pd, Input_Validations& iv) : pd(pd), iv(iv) {}

float fineCalculator::calculate_fines(std::string user, std::string retDate, std::string book_id) {
    for (int i = 0; i < pd.Borrow_details[user].Borrowed_Book.size(); i++) {
        if (book_id == pd.Borrow_details[user].Borrowed_Book[i]) {
            position = i;
            break;
        }
    }

    std::string checkout_date = pd.Borrow_details[user].Borrow_date[position];
    difference = iv.dateDifference(retDate, checkout_date);

    if (difference > 14) {
        days_over = difference - 14;
        result = rate * days_over;

        return result;
    }
    else { return 0; }
}

float fineCalculator::find_user_fines(std::string user) {
    retDate = iv.formattedDate();
    days_over = 0;

    for (int i = 0; i < pd.Borrow_details[user].Borrow_date.size(); i++) {
        difference = iv.dateDifference(retDate, pd.Borrow_details[user].Borrow_date[i]);
        if (difference > 14) {
            days_over += difference - 14;
        }
    }
    if (days_over >= 1) {
        result = rate * days_over;
        return result;
    }
    else { return 0; }
}
