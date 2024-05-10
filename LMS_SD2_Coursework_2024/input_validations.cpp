
#include "validations.h"
#include <chrono>

// Validates the input for various parts of the program. Controls repeatition of regularly used functions.

Input_Validations::Input_Validations(Program_Data& pd) : pd(pd) {}

string Input_Validations::convert_to_upper(string word) {
    for (char& i : word) {
        i = std::toupper(i);
    }
    return word;
}

string Input_Validations::convert_to_lower(string word) {
    for (char& i : word) {
        i = std::tolower(i);
    }
    return word;
}

bool Input_Validations::get_date_string(string word) {
    if (word.size() != 10) {
        return false;
    }

    size_t firstSlash = word.find('/');
    if (firstSlash == string::npos) {
        firstSlash = word.find('-');
        if (firstSlash == string::npos) {
            return false;
        }
    }
    size_t secondSlash = word.find('/', firstSlash + 1);
    if (secondSlash == string::npos) {
        secondSlash = word.find('-', firstSlash + 1);
        if (secondSlash == string::npos) {
            return false;
        }
    }

    string monthStr = word.substr(0, firstSlash);
    string dayStr = word.substr(firstSlash + 1, secondSlash - firstSlash - 1);
    string yearStr = word.substr(secondSlash + 1);

    if (monthStr.size() != 2 || dayStr.size() != 2 || yearStr.size() != 4) {
        return false;
    }

    int month = stoi(monthStr);
    int day = stoi(dayStr);
    int year = stoi(yearStr);

    if (month < 1 || month > 12 || day < 1 || day > 31) {
        return false;
    }

    return true;
}

std::tm Input_Validations::parseDate(const string& dateStr) {
    std::tm date = { 0 }; // Initialize with zeros

    std::istringstream ss(dateStr);
    char delimiter;

    ss >> date.tm_mday >> delimiter >> date.tm_mon >> delimiter >> date.tm_year;

    date.tm_year -= 1900; // Adjust year to be years since 1900
    date.tm_mon -= 1;     // Adjust month to be in range [0, 11]

    return date;
}

int Input_Validations::dateDifference(const string& dateStr1, const string& dateStr2) {
    std::tm date1 = parseDate(dateStr1);
    std::tm date2 = parseDate(dateStr2);

    // Convert tm structures to time_t
    std::time_t time1 = std::mktime(&date1);
    std::time_t time2 = std::mktime(&date2);

    // Calculate the difference in seconds
    long int difference = std::difftime(time1, time2);

    if (difference < 0) {
        return 0;
    }
    else {
        // Convert difference to days
        int daysDifference = difference / (60 * 60 * 24);
        return std::abs(daysDifference); // Return absolute value
    }
}

bool Input_Validations::isDateExpired(const string& date) {
   
    std::stringstream ss(date);
    char delimiter;
    int month, day;
    ss >> day >> delimiter >> month;

    // Get the current time
    std::time_t currentTime;
    std::tm now;
    std::time(&currentTime); // Get current time
    localtime_s(&now, &currentTime); // Convert current time to local time

    // Compare with the provided date
    if (now.tm_mon + 1 > month) { // tm_mon is 0-based
        return false; // Month has passed
    }
    else if (now.tm_mon + 1 == month && now.tm_mday > day) {
        return false; // Month is same but day has passed
    }
    else {
        return true; // Date is still valid
    }
    
}

string Input_Validations::formattedDate() {
    std::time_t currentTime;
    std::time(&currentTime); // get system time

    // convert time to local time
    std::tm localTime;
    localtime_s(&localTime, &currentTime);

    //format for the date so we can do the calculation in dd/mm/yyyy
    char formattedDate[11]; //it is 11 and not 10 cuz of the null terminator to mark the end of a string

    std::strftime(formattedDate, sizeof(formattedDate), "%d/%m/%Y", &localTime);

    string retDate = formattedDate; //auto get system time insted cuz capture input value user can lie to avoid fees.

    return retDate;
}

void Input_Validations::Similar_Titles(string find) {
    cout << "      ID      " << '\t' << " Book Name            " << endl;
    cout << "-------------" << '\t' << "-----------------------" << endl;

    for (const auto& pair : pd.libBooks) {
        string second_comp = convert_to_lower(pair.second.Title);

        if (find == second_comp) {
            cout << pair.first << " : " << '\t' << pair.second.Title << endl;
        }
    }
}

int Input_Validations::match_count(string find) {
    int count = 0;

    for (const auto& pair : pd.libBooks) {
        string second_comp = convert_to_lower(pair.second.Title);

        if (find == second_comp) {
            count += 1;
        }
    }
    return count;
}

string Input_Validations::yes_or_no() {
    cin >> choice;

    while (convert_to_lower(choice) != "yes" && convert_to_lower(choice) != "no") {
        cout << endl << "Invalid. Please enter Yes or No: ";
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin >> choice;
    }

    return convert_to_lower(choice);

}

string Input_Validations::get_current_date() {
    
    // Get the current time point
    auto currentTime = std::chrono::system_clock::now();

    // Convert the time point to a time_t
    std::time_t currentTimeT = std::chrono::system_clock::to_time_t(currentTime);

    // Convert the time_t to a local time tm struct
    std::tm localTime;
    localtime_s(&localTime, &currentTimeT);

    // Convert tm struct to a string
    std::ostringstream oss;
    oss << std::put_time(&localTime, "%c");

    return oss.str();
}

string Input_Validations::search_for_a_book(string msg) {

    std::cout << msg;
    std::cin >> search;
    cout << endl;

    for (const auto& pair : pd.libBooks) {
        std::string find = convert_to_lower(search);
        std::string comp = convert_to_lower(pair.first);
        std::string second_comp = convert_to_lower(pair.second.Title);

        if (find == comp) {
            search = pair.first;
            return search;
            break;
        }
        if (find == second_comp) {
            int match = match_count(find);
            if (match > 1) {
                std::cout << "There are " << match << " " << second_comp << " books!" << endl << endl;
                Similar_Titles(find);
                std::cout << endl << "Please enter the ID for the book you want: ";
                std::string s;
                std::cin >> s;
                s = convert_to_upper(s);
                cout << "The search is: " << s << endl;
                while (pd.libBooks.find(s) == pd.libBooks.end()) {
                    std::cout << "Please enter a valid ID: ";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cin >> s;
                    s = convert_to_upper(s);
                    cout << "The search is: " << s << endl;
                }
                search = s;
                return search;
                break;
            }
            else {
                search = pair.first;
                return search;
                break;
            }
        }
    }

    // Return an empty string if no match is found
    return "";

}

string Input_Validations::find_users_id(string msg){

    cout << msg;
    std::cin >> user_id;
    while ((pd.sys_Users.find(user_id) == pd.sys_Users.end())) {
        std::cout << "User not found. Please enter the correct ID: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> user_id;
    }
    return user_id;
}

bool Input_Validations::check_password(const string& password) {
    std::regex pattern("^(?=.*[a-zA-Z])(?=.*\\d)(?=.*[^a-zA-Z\\d\\s]).{8,}$");
    return std::regex_match(password, pattern);
}

bool Input_Validations::VisaDate(const string& dateStr) {
    // Check if the string has the correct format (MM/YY)
    if (dateStr.size() != 5 || dateStr[2] != '/') {
        return false;
    }

    // Extract month and year from the string
    int month, year;
    if (sscanf_s(dateStr.c_str(), "%d/%d", &month, &year) != 2) {
        return false;
    }

    // Get the current date
    std::time_t currentTime;
    time(&currentTime);
    struct tm currentDate;
    localtime_s(&currentDate, &currentTime);
    int currentYear = currentDate.tm_year % 100; // Last two digits of the current year
    int currentMonth = currentDate.tm_mon + 1; // tm_mon is zero-based

    // Check if the date is in the future
    if (year < currentYear || (year == currentYear && month < currentMonth)) {
        return false;
    }

    // Check if the month is within valid range (1-12)
    if (month < 1 || month > 12) {
        return false;
    }

    // All checks passed, date is valid
    return true;
}

string Input_Validations::getVisaDate() {

    cout << "Expiry Date Format: mm/yy " << endl;
    cout << "Enter the card's expiry date: ";

    cin >> date;
    cout << endl;

    while (!VisaDate(date)) {

        cout << "Expiry Date Format: mm/yy " << endl;
        cout << "Sorry. Please Enter A Valid Date: ";
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin >> date;
        cout << endl << endl;
    }

    return date;
}

int Input_Validations::getPin(){

    cout << "PIN Format: xxx (3 digits) " << endl;
    cout << "Enter the PIN: ";
   
    std::cin >> pin;
    cout << endl;
    
    while (cin.fail() || pin < 100 || pin > 999) {
        cout << endl;
        std::cout << "Please enter a valid 3-digit PIN: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> pin;
    }
    return pin;
}

bool Input_Validations::Validate_SortCode(const string& sortCode) {
    std::regex pattern("^\\d{6}$");
    return std::regex_match(sortCode, pattern);
}

string Input_Validations::getSortCode() {

    while (true) {
        cout << "sort Code Format: xxxxxx (6 digits) " << endl;
        cout << "Enter the bank sort code: ";

        cin >> sortCode;

        if (Validate_SortCode(sortCode)) {
            cout << endl;
            break; 
        }
        else {
            cout << endl;
            cout << "Invalid bank sort code. Please try again." << endl << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    return sortCode;
}

bool Input_Validations::Validate_CardNumber(const string& cardNumber) {

    std::regex pattern(R"(^\d{4}-\d{4}-\d{4}-\d{4}$)");
    return std::regex_match(cardNumber, pattern);
}

string Input_Validations::getVisaNumber() {

    while (true) {
        cout << "Card Number Format: xxxx-xxxx-xxxx-xxxx " << endl;
        cout << "Enter Your 16-digit Credit Card #: ";

        cin >> visaNumber;

        if (Validate_CardNumber(visaNumber)) {
            cout << endl;
            break;
        }
        else {
            cout << endl;
            cout << "Invalid card number. Please try again." << endl << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    return visaNumber;
}

