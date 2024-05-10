#ifndef MANAGE_BOOKS_H
#define MANAGE_BOOKS_H

#include "validations.h"

class ManageBooks {
public:
    ManageBooks(Program_Data& pd, Input_Validations& iv);

    void Register_book();
    void Delete_book();
    void Update_book();
    std::string converttolowercase(std::string word);

private:
    std::string nbTitle;
    std::string nbAuthors;
    int nbYear = 0;
    std::string nbPublisher;
    int nbQTY = 0;
    int nbInStock = 0;
    std::string nbSubjects;
    std::vector<std::string> vectAuthors;
    std::vector<std::string> vect_Update;
    Program_Data& pd;
    Input_Validations& iv;
    std::string search;
    bool found = false;
    int choice = 0;
    int sub_count = 1;
    int diff = 0;
    string msg;
};

#endif 
