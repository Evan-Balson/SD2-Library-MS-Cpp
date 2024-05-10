#ifndef VALIDATIONS_H
#define VALIDATIONS_H

#include <string>
#include "program_data.h"

// Validates the input for various parts of the program. Controls repetition of regularly used functions.
class Input_Validations {
public:
    Input_Validations(Program_Data& pd);

    // Converting string to uppercase by parsing each character.
    std::string convert_to_upper(string word);

    // Converting string to lowercase by parsing each character.
    std::string convert_to_lower(string word);

    // Remember to validate for 30 days in September etc, not 31, and no negative numbers.
    bool get_date_string(string word);

    // Function to parse date string into tm structure.
    std::tm parseDate(const string& dateStr);

    // Function to calculate the difference between two dates in days.
    int dateDifference(const string& dateStr1, const string& dateStr2);

    bool isDateExpired(const string& date);

    // Function to format for the date so we can do the calculation in dd/mm/yyyy.
    std::string formattedDate();

    // Function to find the similarity between titles during user searches.
    void Similar_Titles(string find);

    // This function checks if there are multiple occurrences for similarity.
    int match_count(string find);

    string yes_or_no();

    string get_current_date();

    string search_for_a_book(string msg);

    string find_users_id(string msg);

    bool check_password(const string& password);

    bool VisaDate(const string& dateStr);

    string getVisaDate();

    int getPin();

    bool Validate_SortCode(const string& sortCode);

    string getSortCode();

    bool Validate_CardNumber(const string& cardNumber);

    string getVisaNumber();

private:
    std::string word;
    Program_Data& pd;
    string choice;
    string search;
    bool found = false;
    string msg;
    string user_id;
    string date;
    int pin = 0;
    string sortCode;
    string visaNumber;
};

#endif
