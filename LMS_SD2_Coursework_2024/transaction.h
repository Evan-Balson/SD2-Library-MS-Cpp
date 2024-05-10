#pragma once
# include "program_data.h"
# include "validations.h"


class manage_transactions
{
public:

	manage_transactions(Program_Data& pd, Input_Validations& iv);


	void add_payment_method(string user);
	string process_payment(string user, float fees, string book_id);
	int receipt(string transaction_ID, string user_id, string book_id, float fees);
	

private:
	Program_Data& pd;
	Input_Validations& iv;
	string user;
	string card;
	string code;
	int pin = 0;
	string date;
	string current_date;
	bool validity = false;
	float fees = 0.0;
	string choice;
	string transaction_ID;
	string book_id;

};

