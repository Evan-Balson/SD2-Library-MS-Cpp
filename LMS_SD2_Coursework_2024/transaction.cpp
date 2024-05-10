#include "transaction.h"
#include "System_Directory_Scan.h"



manage_transactions::manage_transactions(Program_Data& pd, Input_Validations& iv) : pd(pd), iv(iv) {}


void manage_transactions::add_payment_method(string user){

	card = iv.getVisaNumber();

	code = iv.getSortCode();

	pin = iv.getPin();

	cout << endl;

	date = iv.getVisaDate();

	pd.Payment_Method[user].card_number = card;
	pd.Payment_Method[user].sortcode = code;
	pd.Payment_Method[user].pin = pin;
	pd.Payment_Method[user].expiration_date = date;

	cout << endl;
	cout << "Card registered successfully." << endl;
	cout << "You can now continue..." << endl << endl;



	/*
	for (const auto& entry : pd.Payment_Method) {
		std::cout << "User: " << entry.first << std::endl;
		std::cout << "Card Number: " << entry.second.card_number << std::endl;
		std::cout << "Sortcode: " << entry.second.sortcode << std::endl;
		std::cout << "PIN: " << entry.second.pin << std::endl;
		std::cout << "Expiration Date: " << entry.second.expiration_date << std::endl;
		std::cout << std::endl;
	}
	*/
}

string manage_transactions::process_payment(string user, float fees, string book_id){

	date = pd.Payment_Method[user].expiration_date;
	validity = iv.isDateExpired(date);
	if (validity == true) {
	/*process payment*/
		/*generating transaction ID*/
		transaction_ID = "UK-BANK-" + to_string(pd.Transaction_IDC);
		pd.Transaction_IDC += 1;

		receipt(transaction_ID, user, book_id, fees);
		cout << "Payment Successfull!" << endl;


	}
	else {

		/*prompt for new payment method*/
		cout << "Payment method has expired." << endl << endl;
		cout << "Add new payment method now? Yes/No: ";
		choice = iv.yes_or_no();

		cout << endl;

		if (choice == "yes") {
			add_payment_method(user);
			string transact = process_payment(user, fees, book_id);
			return transact;
			
		}
		else {
			cout << "Returning to dashboard." << endl << endl;
			return "failed";
		}
	}

	return transaction_ID;
}



// reciept layout
int manage_transactions::receipt(string transaction_ID, string user_id, string book_id, float fees) {

	//initializing system object
	System_Directory_Scan system;


	// create name the new directory for receipts:
	string newDirPath = "receipts";
	string fullPath;

	// creating the filne name string with transaction_ID:
	string filename = "receipts/receipt-" + transaction_ID +".txt";

	// Create the directory
	if (system.createDirectory(newDirPath, fullPath)) {
		cout << endl;
		//std::cout << "New directory path: " << fullPath << std::endl;
	}

	// Open the file for writing
	ofstream outputFile(filename);

	// Check if the file is opened successfully
	if (!outputFile) {
		cerr << "Failed to open the file." << endl;
		return 1;
	}

	
	// Get the length of the string
	size_t length = pd.Payment_Method[user_id].card_number.length();

	// Get the last four characters using substr
	std::string lastFour = pd.Payment_Method[user_id].card_number.substr(length - 4);

	// Write the receipt content to the file
	outputFile << "STEPWISE UNIVERSITY LIBRARY POS" << endl;
	outputFile << "     50032 Eaton Drive" << endl;
	outputFile << "         Digby 528" << endl;
	outputFile << "   South Ham London 4HJ01" << endl;
	outputFile << "        United Kingdom" << endl << endl;

	outputFile << "      " << iv.get_current_date() << endl;
	outputFile << "    Order ID: " << transaction_ID << endl;
	outputFile << " ----------------------------" << endl << endl;

	outputFile << " Book ID:     " << book_id << endl;
	outputFile << " Fee:" << "\t" << "\t" << "\t" << fees << endl << endl;

	outputFile << " Sub Total:" << "\t" << "\t" << fees << endl;
	outputFile << "----------------------------" << endl << endl;

	outputFile << " Grand Total:" << "\t" << "\t" << fees << endl;
	outputFile << " ----------------------------" << endl << endl;

	outputFile << "Card:\tXXXX-XXXX-XXXX-" << lastFour << endl;
	outputFile << "        THANK YOU!" << endl << endl;

	// Close the file
	outputFile.close();

	int  print = system.launch_receipt_file(filename);

	if (print == 1) {
	
		cout << "Sorry, cannot detect operating system." << endl;
	}
	return 0;
}


