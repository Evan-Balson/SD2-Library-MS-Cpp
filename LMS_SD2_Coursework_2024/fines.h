#ifndef FINE_CALCULATOR_H
#define FINE_CALCULATOR_H


#include "validations.h"

class fineCalculator {
public:
    fineCalculator(Program_Data& pd, Input_Validations& iv);

    float calculate_fines(std::string user, std::string retDate, std::string book_id);
    float find_user_fines(std::string user);

private:
    float rate = 0.20;
    int days_over = 0;
    Program_Data& pd;
    Input_Validations& iv;
    int difference = 0;
    int position = 0;
    float result = 0.00;
    std::string retDate;
};

#endif /* FINE_CALCULATOR_H */
