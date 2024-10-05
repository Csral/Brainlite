#include "includes/utils.hpp"
#include "includes/errors.hpp"

int toInt(const std::string& num, const std::string& int_line) {
    int res = 0;

    for (char digit : num) {  // Loop through each character in the string
        if (digit < '0' || digit > '9') {  // Check if character is not a digit
            std::stringstream err_msg;
            err_msg << "Expected number as argument but received " << num << "\nAt: " << int_line << "\n";
            throw std::invalid_argument(err_msg.str());
        }
        res = res * 10 + (digit - '0');  // Accumulate the integer value
    }

    return res;
};