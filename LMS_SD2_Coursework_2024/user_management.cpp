
#include "manage_user.h"

Manage_users::Manage_users(Program_Data& pd, Input_Validations& iv) : pd(pd), iv(iv) {}



    void Manage_users::Register_user() {

        string fName;
        string lName;


        cout << "Enter the first name: ";
        cin >> fName;
        while (fName.length() < 3) {
            std::cout << std::endl << "Sorry. First name must have 3 characters minimum: ";
            std::cin >> fName;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        fName = iv.convert_to_upper(fName);
        cout << endl;


        cout << "Enter the last name: ";
        cin >> lName;
        while (lName.length() < 3) {
            std::cout << std::endl << "Sorry. Last name must have 3 characters minimum: ";
            std::cin >> lName;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        lName = iv.convert_to_upper(lName);
        cout << endl;


        nwName = fName + " " + lName;

        cout << "Enter the role: ";
        while (!(cin >> nwRole) || (iv.convert_to_lower(nwRole) != "student" && iv.convert_to_lower(nwRole) != "librarian")) {
            cout << "Please enter student or librarian as the role: ";
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        nwRole = iv.convert_to_lower(nwRole);
        cout << endl;


        do {
            std::cout << "Enter the password: ";
            std::cin >> nwpassword;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << endl << endl;

            if (nwpassword.length() < 8 || !iv.check_password(nwpassword)) {
                std::cout << "Password must be 8 characters long and include numbers, letters, and symbols." << std::endl;
            }
        } while (nwpassword.length() < 8 || !iv.check_password(nwpassword));
        cout << endl;


        pd.latest_UID = pd.latest_UID + 1;
        string UIDGen = nwName.substr(0, 3) + std::to_string(pd.latest_UID); // come up with a id generator class
            
        cout << "Please take note: " << endl << fName << "'s login ID is: " << UIDGen << endl;
        cout << endl;

        pd.sys_Users.insert({
        { UIDGen, {nwName, nwpassword, nwRole, nwlist}} });


    }

    void Manage_users::Remove_user() {
        cout << "Enter the user ID: ";
        cin >> search;
        cout << endl << endl;

        if (pd.sys_Users.find(search) != pd.sys_Users.end()) {
            if (pd.sys_Users[search].currentBook.empty()) {

                string tempName = pd.sys_Users[search].user_name;
                pd.sys_Users.erase(search);
                cout << tempName << " Has been removed from the system." << endl;


            }
            else {

                cout << "Sorry. This user has not yet returned a book." << endl;
                cout << "Stock must be collected before deletion." << endl;

            }
        }
        else
        {
            cout << "This ID does not match any existing Users. " << endl;
        }

    }

    void Manage_users::Update_user() {
        string fName;
        string lName;

        // enter the user ID.
        cout << "Please The User ID For The Update: ";
        cin >> search;
        search = iv.convert_to_upper(search);
        cout << endl;

        if (pd.sys_Users.find(search) != pd.sys_Users.end()) {

            cout << "Enter the first name: ";
            cin >> fName;
            while (fName.length() < 3) {
                std::cout << std::endl << "Sorry. First name must have 3 characters minimum: ";
                std::cin >> fName;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            fName = iv.convert_to_upper(fName);
            cout << endl;

            cout << "Enter the last name: ";
            cin >> lName;
            while (lName.length() < 3) {
                std::cout << std::endl << "Sorry. Last name must have 3 characters minimum: ";
                std::cin >> lName;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            lName = iv.convert_to_upper(lName);
            cout << endl;

            // combine the first name and last name
            nwName = fName + " " + lName;

            cout << "Enter the role: ";
            while (!(cin >> nwRole) || (iv.convert_to_lower(nwRole) != "student" && iv.convert_to_lower(nwRole) != "librarian")) {
                cout << "Please enter student or librarian as the role: ";
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            nwRole = iv.convert_to_lower(nwRole);
            cout << endl;

            do {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Enter the password: ";
                std::cin >> nwpassword;
                if (nwpassword.length() < 8 || !iv.check_password(nwpassword)) {
                    std::cout << "Password must be 8 characters long and include numbers, letters, and symbols." << std::endl;
                }
            } while (nwpassword.length() < 8  || !iv.check_password(nwpassword));
            cout << endl;



            pd.sys_Users[search].user_name = nwName;
            pd.sys_Users[search].role = nwRole;
            pd.sys_Users[search].password = nwpassword;
        }
        else
        {
            cout << "This ID does not match any existing Users. " << endl;
        }




    }

