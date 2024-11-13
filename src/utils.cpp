#include "includes/utils.hpp"
#include "includes/errors.hpp"

int toInt(const std::string& num) {
    int res = 0;

    for (char digit : num) {  // Loop through each character in the string
        if (digit < '0' || digit > '9') {  // Check if character is not a digit
            std::stringstream err_msg;
            err_msg << "Expected number as argument but received " << num << "\n";
            throw std::invalid_argument(err_msg.str());
        }
        res = res * 10 + (digit - '0');  // Accumulate the integer value
    }

    return res;
};

int ringBuffer(const int& number) {

    int diff = number - 256;
    bool useDiff = (diff > 0);

    while (diff > 255) {

        diff -= 256;

    };

    return (useDiff) ?  diff : number;

};

int ascii(const char& letter) {

    int id = (int) letter;

    id = ringBuffer(id);

    return id;

};

bool endQuestionMark(const std::string& str) {

    auto toEnd = str.end();

    while (toEnd != str.begin() && (std::isspace(*(--toEnd)) || *toEnd == '\n'));

    return toEnd != str.begin() && *toEnd == '?';

};

std::string strip(const std::string& str, const char& reference = ' ', const std::string& replace = "") {

    std::string result = "";

    for (char letter : str) (letter == ' ' || letter == reference) ? result += replace : result += letter;

    return result;

};