/*

  Copyright 2025 Chaturya Reddy (@Csral) <chaturyasral@gmail.com>

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

*/

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

std::string strip(const std::string& str, const char& reference, const std::string& replace) {

    std::string result = "";

    for (char letter : str) (letter == ' ' || letter == reference) ? result += replace : result += letter;

    return result;

};