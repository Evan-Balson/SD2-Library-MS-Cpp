/*
* 
book_management.cpp

*/

#include "manage_books.h"

ManageBooks::ManageBooks(Program_Data& pd, Input_Validations& iv) : pd(pd), iv(iv) {}

    void ManageBooks::Register_book() {

        cout << endl;
        cout << "Enter The New Title: ";
        cin >> nbTitle;
        while (nbTitle.length() < 4) {
            std::cout << std::endl << "Sorry. Title must have 4 characters minimum: ";
            std::cin >> nbTitle;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        nbTitle = iv.convert_to_upper(nbTitle);
        cout << endl;


        while (nbAuthors != "END") {
            if (sub_count > 1) {
                cout << "Enter 'End' to stop or " << endl;
                cout << "Enter authour # " << sub_count << ": ";

            }
            else {
                cout << "Enter 'End' to skip or " << endl;
                cout << "Enter The New Authors: ";
            }

            cin >> nbAuthors;
            nbAuthors = iv.convert_to_upper(nbAuthors);


            if (nbAuthors != "end") {
                vectAuthors.push_back(nbAuthors);
            }
            sub_count += 1;
            cout << endl;
        }
        sub_count = 1;
        cout << endl;

        cout << "Enter The New year: ";
        while (!(std::cin >> nbYear) || std::to_string(nbYear).length() != 4 || nbYear > 2024) { // Validate year format
            std::cout << "Please enter a valid year: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        cout << endl;

        cout << "Enter The New publisher: ";
        cin >> nbPublisher;
        nbPublisher = iv.convert_to_upper(nbPublisher);
        cout << endl;


        cout << "Enter The New quantity: ";
        while (!(cin >> nbQTY) || nbQTY <= 0) {

            cout << "Please enter a positive integer: ";
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        cout << endl;

        //assign stock.

        nbInStock = nbQTY;

        while (nbSubjects != "END") {
            if (sub_count > 1) {
                cout << "Enter 'End' to stop or " << endl;
                cout << "Enter subject # " << sub_count << ": ";

            }
            else {
                cout << "Enter 'End' to skip or " << endl;
                cout << "Enter The New subjects: ";

            }

            cin >> nbSubjects;
            nbSubjects = iv.convert_to_upper(nbSubjects);


            if (nbSubjects != "end") {
                vect_Update.push_back(nbSubjects);
            }
            sub_count += 1;
            cout << endl;
        }
        sub_count = 1;
        cout << endl;

        pd.latest_BID = pd.latest_BID + 1;
        string UIDGen = std::to_string(pd.latest_BID) + nbTitle.substr(0, 4) + std::to_string(nbYear); // come up with a id generator class

        pd.libBooks.insert({
        { {UIDGen},{nbTitle, vectAuthors, nbYear, nbPublisher, nbQTY, nbInStock, vect_Update }} });

        nbAuthors = "";
        nbSubjects = "";


    }

    void ManageBooks::Delete_book() {
        msg = "Enter the book ID: ";
        search = iv.search_for_a_book(msg);


        if (search != "") {
            if (pd.libBooks[search].InStock == pd.libBooks[search].QTY) {

                pd.libBooks.erase(search);

            }
            else {

                cout << "Sorry. It seems a book is still rented out." << endl;
                cout << "Stock must be collected before deletion." << endl;

            }
        }
        else
        {
            cout << "This ID does not match any existing Books. " << endl;
        }


    }

    void ManageBooks::Update_book() {

        cout << endl;
        // enter the book ID or Title to start update.
        string msg = "Please Enter The Book Title or ID For The Update: ";

        search = iv.search_for_a_book(msg);

        cout << endl;

        if (search != "") {

            cout << "Options:" << endl;
            cout << "1. Update All Details for this Entry." << endl;
            cout << "2. Update Title ONLY." << endl;
            cout << "3. Update the author ONLY." << endl;
            cout << "4. Update the year ONLY." << endl;
            cout << "5. Update the Publisher ONLY." << endl;
            cout << "6. Update the Quantity ONLY." << endl;
            cout << "7. Update the subjects ONLY." << endl;
            cout << "8. Cancel." << endl << endl;

            cout << "Enter a number from the menu above: ";
            while (!(cin >> choice) || choice < 1 || choice > 8) {
                cout << "Invalid. Enter an integer from 1-8: ";
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }

            switch (choice) {

            case 1:
                //1. Update All Details for this Entry
                cout << "Enter The New Title: ";
                cin >> nbTitle;
                while (nbTitle.length() < 4) {
                    std::cout << std::endl << "Sorry. Title must have 4 characters minimum: ";
                    std::cin >> nbTitle;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                nbTitle = iv.convert_to_upper(nbTitle);
                cout << endl;


                while (nbAuthors != "END") {
                    if (sub_count > 1) {
                        cout << "Enter 'End' to stop or " << endl;
                        cout << "Enter authour # " << sub_count << ": ";

                    }
                    else {
                        cout << "Enter 'End' to skip or " << endl;
                        cout << "Enter The New Authors: ";
                    }

                    cin >> nbAuthors;
                    nbAuthors = iv.convert_to_upper(nbAuthors);


                    if (nbAuthors != "end") {
                        vectAuthors.push_back(nbAuthors);
                    }
                    sub_count += 1;
                    cout << endl;
                    
                }
                sub_count = 1;
                cout << endl;

                cout << "Enter The New year: ";
                while (!(std::cin >> nbYear) || std::to_string(nbYear).length() != 4 || nbYear > 2024) { // Validate year format
                    std::cout << "Please enter a valid year: ";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                cout << endl;

                cout << "Enter The New publisher: ";
                cin >> nbPublisher;
                nbPublisher = iv.convert_to_upper(nbPublisher);
                cout << endl;

                diff = pd.libBooks[search].QTY - pd.libBooks[search].InStock;

                cout << "Enter The New quantity: ";
                while (!(cin >> nbQTY) || nbQTY < diff || nbQTY <= 0) { // Validate year format
                    if (nbQTY < diff) {
                        cout << diff << "Books are currently rented." << endl;
                        cout << "Enter atleast " << diff << " : ";

                    }
                    else {
                        cout << "Please enter a positive integer: ";

                    }
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                cout << endl;

                if (pd.libBooks[search].QTY > nbQTY) {

                    nbInStock = pd.libBooks[search].InStock - (pd.libBooks[search].QTY - nbQTY);

                }
                else if (pd.libBooks[search].QTY < nbQTY) {

                    nbInStock = pd.libBooks[search].InStock + (nbQTY - pd.libBooks[search].QTY);


                }
                else { // pd.libBooks[search].QTY == nbQTY

                    nbInStock = pd.libBooks[search].InStock;

                }

                while (nbSubjects != "END") {
                    if (sub_count > 1) {
                        cout << "Enter 'End' to stop or " << endl;
                        cout << "Enter subject # " << sub_count << ": ";

                    }
                    else {
                        cout << "Enter 'End' to skip or " << endl;
                        cout << "Enter The New subjects: ";
                    }

                    cin >> nbSubjects;
                    nbSubjects = iv.convert_to_upper(nbSubjects);


                    if (nbSubjects != "end") {
                        vect_Update.push_back(nbSubjects);
                    }
                    sub_count += 1;
                    cout << endl;
                }
                sub_count = 1;
                cout << endl;

                // update values
                pd.libBooks[search].Title = nbTitle;
                pd.libBooks[search].Authors = vectAuthors;
                pd.libBooks[search].Year = nbYear;
                pd.libBooks[search].Publisher = nbPublisher;
                pd.libBooks[search].QTY = nbQTY;
                pd.libBooks[search].InStock = nbInStock;
                pd.libBooks[search].Subjects = vect_Update;

                nbAuthors = "";
                nbSubjects = "";

                break;

            case 2:
                //2. Update Title ONLY
                cout << "Enter The New Title: ";
                cin >> nbTitle;
                while (nbTitle.length() < 4) {
                    std::cout << std::endl << "Sorry. Title must have 4 characters minimum: ";
                    std::cin >> nbTitle;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                nbTitle = iv.convert_to_upper(nbTitle);
                cout << endl;

                // update values
                pd.libBooks[search].Title = nbTitle;


                break;

            case 3:
                //3. Update the authorONLY: Ask for #of entries then loop for insertion into a temporary list. just update all. 


                while (nbAuthors != "END") {
                    if (sub_count > 1) {
                        cout << "Enter 'End' to stop or " << endl;
                        cout << "Enter authour # " << sub_count << ": ";

                    }
                    else {
                        cout << "Enter 'End' to skip or " << endl;
                        cout << "Enter The New Authors: ";
                    }

                    cin >> nbAuthors;
                    nbAuthors = iv.convert_to_upper(nbAuthors);


                    if (nbAuthors != "end") {
                        vectAuthors.push_back(nbAuthors);
                    }
                    sub_count += 1;
                    cout << endl;
                }
                sub_count = 0;
                cout << endl;

                // update values
                pd.libBooks[search].Authors = vectAuthors;
                nbAuthors = "";


                break;

            case 4:
                //4. Update the year ONLY

                cout << "Enter The New year: ";
                while (!(std::cin >> nbYear) || std::to_string(nbYear).length() != 4 || nbYear > 2024) { // Validate year format
                    std::cout << "Please enter a valid year: ";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                cout << endl;
                // update values

                pd.libBooks[search].Year = nbYear;


                break;

            case 5:
                //5. Update the Publisher ONLY
                cout << "Enter The New publisher:";
                cin >> nbPublisher;
                nbPublisher = iv.convert_to_upper(nbPublisher);
                cout << endl;

                // update values

                pd.libBooks[search].Publisher = nbPublisher;


                break;

            case 6:
                //6. Update the Quantity ONLY

                diff = pd.libBooks[search].QTY - pd.libBooks[search].InStock;

                cout << "Enter The New quantity: ";
                while (!(cin >> nbQTY) || nbQTY < diff || nbQTY <= 0) { // Validate year format
                    if (nbQTY < diff) {
                        cout << diff << "Books are currently rented." << endl;
                        cout << "Enter atleast " << diff << " : ";

                    }
                    else {
                        cout << "Please enter a positive integer: ";

                    }
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                cout << endl;

                if (pd.libBooks[search].QTY > nbQTY) {

                    nbInStock = pd.libBooks[search].InStock - (pd.libBooks[search].QTY - nbQTY);

                }
                else if (pd.libBooks[search].QTY < nbQTY) {

                    nbInStock = pd.libBooks[search].InStock + (nbQTY - pd.libBooks[search].QTY);


                }
                else { // pd.libBooks[search].QTY == nbQTY

                    nbInStock = pd.libBooks[search].InStock;

                }

                // update values

                pd.libBooks[search].QTY = nbQTY;
                pd.libBooks[search].InStock = nbInStock;


                break;

            case 7:
                //7. Update the subjects ONLY

                while (nbSubjects != "END") {
                    if (sub_count > 1) {
                        cout << "Enter 'End' to stop or " << endl;
                        cout << "Enter subject # " << sub_count << ": ";

                    }
                    else {
                        cout << "Enter 'End' to skip or " << endl;
                        cout << "Enter The New subjects: ";
                    }

                    cin >> nbSubjects;
                    nbSubjects = iv.convert_to_upper(nbSubjects);


                    if (nbSubjects != "end") {
                        vect_Update.push_back(nbSubjects);
                    }
                    sub_count += 1;
                    cout << endl;
                }
                sub_count = 0;
                cout << endl;

                // update values
                pd.libBooks[search].Subjects = vect_Update;

                nbSubjects = "";


                break;

            case 8:
                //8. cancel operation 
                break;

            }

        }
        else { cout << "This book does not exist in our library." << endl << endl; }
    }
