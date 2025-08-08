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

#include "includes/brainuf.hpp"
#include "includes/errors.hpp"
#include "includes/utils.hpp"

void brainlite::exec_func(const std::string& tokenId, const std::unordered_map<std::string, std::function<void()>>& no_args) {

    auto find_fn = no_args.find(tokenId);

    if (find_fn != no_args.end()) {
        find_fn->second();
    };

};

void brainlite::debug_tester(void) {

    for (std::string code : compiled_code) {
        std::cout << code << std::endl;
    };

};

brainlite::brainlite() { // * Constructor

    pointer = new uint64_t(0); // ! Pointer starts at 0
    argsCollectedLength = 0;
    current_line = new std::string;
    skipIfError = false;
    memory_pointer = 0;
    internalSet = false;
    internalVal = 0;

    validTokens.insert("set");
    validTokens.insert("move");
    validTokens.insert("loop");
    validTokens.insert("front");
    validTokens.insert("right");
    validTokens.insert("back");
    validTokens.insert("left");
    validTokens.insert("inc");
    validTokens.insert("dec");
    validTokens.insert("inctill");
    validTokens.insert("dectill");
    validTokens.insert("print");
    validTokens.insert("whatis");
    validTokens.insert("end");
    validTokens.insert("out");
    validTokens.insert("input");

    execTokens["set"] = [this]() { this->set(); };
    execTokens["front"] = [this]() { this->front(); };
    execTokens["right"] = [this]() { this->front(); };
    execTokens["back"] = [this]() { this->back(); };
    execTokens["left"] = [this]() { this->back(); };
    execTokens["move"] = [this]() { this->move(); };
    execTokens["inc"] = [this]() { this->inc(); };
    execTokens["inctill"] = [this]() { this->inctill(); };
    execTokens["dec"] = [this]() { this->dec(); };
    execTokens["dectill"] = [this]() { this->dectill(); };
    execTokens["print"] = [this]() { this->print(); };
    execTokens["input"] = [this]() { this->input(); };
    execTokens["loop"] = [this]() { this->loop(); };
    execTokens["whatis"] = [this]() { this->whatis(); };
    execTokens["end"] = [this]() { this->end_loop(); };
    execTokens["out"] = [this]() { this->out(); };

};

brainlite::~brainlite() { // * Destructor
    if (pointer) delete pointer;  // Free dynamically allocated memory
    if (current_line) delete current_line;
};

std::vector<std::string> brainlite::getCode(void) {
    return compiled_code; // get transpiled code.
};

int brainlite::validate(const std::string& token) {

    /*
    
        * Returns the count of token encountered by lexCode() in validTokens
        * Simply say, if token is not a valid token then count would be 0 which is boolean false.
        * So token is not valid else it is valid.
    
    */

    return validTokens.count(token);

};

void brainlite::lexCode(std::string line) {

    /*
        * Main logic wise lexer.
    */

    *current_line = line;
    skipIfError = false;

    if (line.empty()) return;
    if (line.at(0) == '#') return; // ! Comment

    if (endQuestionMark(line)) {
        skipIfError = true;
    };

    std::string collection = "";

    for (uint64_t i = 0; i < line.length(); i++) {

        *pointer = i;
        if (i+1 == line.length())
            collection += line.at(i);

        if (line.at(i) == ' ' || line.at(i) == '\n' || i+1 == line.length() || line.at(i) == ';') { // * consider to obtain a token.

            if (collection.empty()) continue;

            if (!validate(collection)) {
                if (!skipIfError) {
                    
                    delete pointer;
                    delete current_line;

                    std::cerr << collection << " is not a valid keyword\nAt: " << line << std::endl;
                    exit(COMPILER_ERR_INVALID_KEYWORD);

                };
            }; // * Verify if the keyword is right.

            exec_func(collection,execTokens);
            i += argsCollectedLength;

        } else {
            collection += line.at(i);
        };

    };

}

/*

!   Class Alone Functions
!   Class Alone Functions
!   Class Alone Functions

*/

int brainlite::currentValue(void) {

    //* Assumes that there would be no complex statement elements, i.e., statements like "+++>" or such.

    int value = 0;
    int i = compiled_code.size()-1;

    while (i > -1) {

        if (compiled_code.at(i).find(">") != std::string::npos || compiled_code.at(i).find("<") != std::string::npos) {
            break;
        } else {

            for (char miniToken : compiled_code.at(i)) {
               
                if (miniToken == '+') {

                    if (value == 255)
                        value = -1;
                    value++;

                } else if (miniToken == '-') {
                    
                    if (value == 0)
                        value = 256;

                    value--;

                } else continue;

            };

        };

        i--;

    };

    return value;

};

void brainlite::set(void) {

    //* Return type: No. of characters read for input.
    //* Current element becomes looper

    std::string args = "";
    std::string code = "";
    int toSet = 0;
    uint64_t j = (*pointer)+1;

    int looper = 0;

    if (internalSet) {
        toSet = internalVal;
    } else {

        for (;j<current_line->length();j++) {

            if (current_line->at(j) == ' ' || current_line->at(j) == '\n' || current_line->at(j) == ';') { // * The line/args ended.

                // * Our arg must be a num!
                // * Validate by isNan
                // * now generate the code for this.

                if (args.length() == 0) {

                    if (skipIfError) return;

                    delete pointer;
                    delete current_line;

                    std::cerr << "Expected an argument for the keyword set, Received None. \n"
                            << "At: " << *current_line << "\n";
                    exit(COMPILER_ERR_SET_KEYWORD_MISSING_ARGUMENT);

                }

                break;

            };

            args += current_line->at(j);

        };

        // * now, find the best way to write a code for doing toSet using gcd.
        toSet = toInt(args);
        toSet = ringBuffer(toSet);
    
    };

    while (looper < toSet) {

        code += "+";
        looper++;

    };

    //* Logic: Loop 4 times with greatest of num/4 and then remove extra 4's form ceil.

    compiled_code.push_back(code);
    argsCollectedLength = j;

};

void brainlite::front(void) {

    compiled_code.push_back(">");
    memory_pointer++;

};

void brainlite::back(void) {

    compiled_code.push_back("<");
    memory_pointer--;

};

inline void brainlite::inc(void) noexcept {

    //* Increases one bit
    compiled_code.push_back("+");

};


inline void brainlite::dec(void) noexcept {

    //* Increases one bit
    compiled_code.push_back("-");

};

void brainlite::inctill(void) {

    //* Increases n bit
    //* Return type: No. of characters read for input.

    std::string args = "";
    std::string code = "";
    int toSet = 0;
    uint64_t j = (*pointer)+1;
    int looper = brainlite::currentValue();

    for (;j<current_line->length();j++) {

        if (current_line->at(j) == ' ' || current_line->at(j) == '\n' || current_line->at(j) == ';') { // * The line/args ended.

            // * Our arg must be a num!
            // * Validate by isNan
            // * now generate the code for this.

            if (args.length() == 0) {

                if (skipIfError) return;

                delete pointer;
                delete current_line;

                std::cerr << "Missing numeric argument after 'inctill' keyword.\n"
                        << "At: " << *current_line << "\n";
                exit(COMPILER_ERR_INCTILL_MISSING_ARGUMENT);

            }

            break;

        };

        args += current_line->at(j);

    };

    toSet = toInt(args);
    toSet = ringBuffer(toSet);

    while (looper < toSet) {

        code += "+";
        looper++;

    };

    compiled_code.push_back(code);
    argsCollectedLength = j;

};

void brainlite::dectill(void) {

    //* dec n bit
    //*Return type: No. of characters read for input.

    std::string args = "";
    std::string code = "";
    int toSet = 0;
    uint64_t j = (*pointer)+1;
    int looper = brainlite::currentValue();

    for (;j<current_line->length();j++) {

        if (current_line->at(j) == ' ' || current_line->at(j) == '\n' || current_line->at(j) == ';') { // * The line/args ended.

            // * Our arg must be a num!
            // * Validate by isNan
            // * now generate the code for this.

            if (args.length() == 0) {

                if (skipIfError) return;

                delete pointer;
                delete current_line;

                std::cerr << "Missing numeric argument after 'dectill' keyword.\n"
                        << "At: " << *current_line << "\n";
                exit(COMPILER_ERR_DECTILL_MISSING_ARGUMENT);

            }

            break;

        };

        args += current_line->at(j);

    };

    toSet = toInt(args);

    while (looper > toSet) {

        code += "-";
        toSet++;

    };

    compiled_code.push_back(code);
    argsCollectedLength = j;

};

void brainlite::move(void) {

    //* move n bit
    //* Return type: No. of characters read for input.

    std::string args = "";
    std::string code = "";
    int toMove = 0;
    uint64_t j = (*pointer)+1;
    int looper = 0;

    bool backwards = false;

    if (current_line->at(j) == '-') {
        // * Reverse move (backwards moving.)
        backwards = true;
        j++;
    };

    for (;j<current_line->length();j++) {

        if (current_line->at(j) == ' ' || current_line->at(j) == '\n' || current_line->at(j) == ';') { // * The line/args ended.

            // * Our arg must be a num!
            // * Validate by isNan
            // * now generate the code for this.

            if (args.length() == 0) {

                delete pointer;
                delete current_line;

                std::cerr << "Missing numeric argument after 'move' keyword.\n"
                        << "At: " << *current_line << "\n";
                exit(COMPILER_ERR_MOVE_MISSING_ARGUMENT);

            }

            break;

        };

        args += current_line->at(j);

    };

    toMove = toInt(args);

    if (toMove == 0) {

        while (memory_pointer > 0) {
            code += "<";
            memory_pointer--;
        };

    } else {

        if (backwards) {

            while (looper < toMove) {

                code += "<";
                memory_pointer--;
                looper++;

            };
        
        } else {

            while (looper < toMove) {

                code += ">";
                memory_pointer++;
                looper++;

            };

        };

    };

    compiled_code.push_back(code);
    argsCollectedLength = j;

};

void brainlite::print(void) {

    std::string args = "";
    uint64_t j = (*pointer)+1;
    
    bool ended = false;

    if (current_line->at(j) != '"') {

        if (skipIfError) return;

        delete pointer;
        delete current_line;

        std::cerr << "Expected \" after print statement. Found none\n"
                << "At: " << *current_line << "\n";
        exit(COMPILER_ERR_PRINT_MISSING_QUOTE);

    };

    j++; // * This is done so that the pointer moves forward by unity and allows for the pointer to be set at the start of string.

    for (;j<current_line->length();j++) {

        if (current_line->at(j) == '"') {
            ended = true;
        };

        if (current_line->at(j) == '"' || current_line->at(j) == ';') { // * The line/args ended.

            // * Our arg must be a num!
            // * Validate by isNan
            // * now generate the code for this.

            if (!ended) {

                if (skipIfError) return;

                std::cerr << "Expected \" after print statement. Found none\n"
                        << "At: " << *current_line << "\n";
                exit(COMPILER_ERR_PRINT_MISSING_QUOTE);

            } else if (args.length() == 0) {

                if (skipIfError) return;

                delete pointer;
                delete current_line;

                std::cerr << "Expected an argument for the keyword print, Received None. \n"
                        << "At: " << *current_line << "\n";
                exit(COMPILER_ERR_PRINT_MISSING_ARGUMENT);

            };

            break;

        };

        args += current_line->at(j);

    };

    if (!ended) {
        if (skipIfError) return;

        std::cerr << "Expected \" after print statement. Found none\n"
                << "At: " << *current_line << "\n";
        exit(COMPILER_ERR_PRINT_MISSING_QUOTE);
    }

    internalSet = true;

    for (uint64_t i = 0; i < args.length(); i++) {

        char letter = args[i];

        if (letter == '\\'  && i + 1 < args.size()) {

            internalVal = 0;

            char nextLetter = args[i+1];

            if (nextLetter == 'n') {
                internalVal = ascii('\n');
                i++;
            } else if (nextLetter == 't') {
                internalVal = ascii('\t');
                i++;
            } else if (nextLetter == '\\') {
                internalVal = ascii(letter);
                i++;
            }

        } else {
            internalVal = ascii(letter);
        }

        brainlite::set();
        compiled_code.push_back(".>");

    };

    internalSet = false;
    argsCollectedLength = j;

};

void brainlite::input(void) {

    std::string args = "";
    std::string code = "";
    int toSet = 0;
    uint64_t j = (*pointer)+1;

    int looper = 0;

    if (internalSet) {

        toSet = internalVal;

    } else {

        for (;j<current_line->length();j++) {

            if (current_line->at(j) == ' ' || current_line->at(j) == '\n' || current_line->at(j) == ';') { // * The line/args ended.

                // * Our arg must be a num!
                // * Validate by isNan
                // * now generate the code for this.

                if (args.length() == 0) {

                    if (skipIfError) return;

                    delete pointer;
                    delete current_line;

                    std::cerr << "Expected an argument for the keyword input, Received None. \n"
                            << "At: " << *current_line << "\n";
                    exit(COMPILER_ERR_INPUT_MISSING_ARGUMENT);

                }

                break;

            };

            args += current_line->at(j);

        };

        // * now, find the best way to write a code for doing toSet using gcd.
        toSet = toInt(args);
    
    };

    while (looper < toSet) {

        code += ",";
        looper++;

    };

    // ! Logic: Loop 4 times with greatest of num/4 and then remove extra 4's form ceil.

    compiled_code.push_back(code);

    argsCollectedLength = j;

};

void brainlite::loop(void) {

    /*
    Syntax:
    *    loop how many times
    * things to do in loop
    * end
    * current/higher/lower -> current is denoted by 0. Current memory address/pointer is used as looper.
    * higher is denoted by 1, it means to use next memory address as the looper
    * lower means to use the memory address behind as looper
    * end -> marks end of loop (writes '-]' at end of code.
    */

   std::string args = "";
   std::string code = "";

   uint64_t j = (*pointer)+1; 
   
    for (;j<current_line->length();j++) {

        if (current_line->at(j) == ' ' || current_line->at(j) == '\n' || current_line->at(j) == ';') { // * The line/args ended.

            // * Our first arg must be a num!
            // * Validate by isNan
            // * now generate the code for this.

            if (args.length() == 0) {

                if (skipIfError) return;

                delete pointer;
                delete current_line;

                std::cerr << "Expected an argument for the keyword input, Received None. \n"
                        << "At: " << *current_line << "\n";
                exit(COMPILER_ERR_INPUT_MISSING_ARGUMENT_SECOND_OCCURRENCE);

            }

            break;

        };

        args += current_line->at(j);

    };

    internalSet = true;
    internalVal = toInt(args);

    brainlite::set(); // set number of times to loop at current address.

    internalSet = false;
    internalVal = 0;

    isLooping = true; // set looping flag.

    looperAddress.push_back(memory_pointer); // set current memory pointer as base address

    argsCollectedLength = j; // return to lexer for normal lexing.

};

void brainlite::whatis(void) {

    std::string args = "";
    uint64_t j = (*pointer)+1;
    
    bool ended = false;
    std::string code = "";

    if (current_line->at(j) != '"') {

        if (skipIfError) return;

        delete pointer;
        delete current_line;

        std::cerr << "Expected \" after whatis statement. Found none\n"
                << "At: " << *current_line << "\n";
        exit(COMPILER_ERR_WHATIS_MISSING_QUOTE);
        
    };

    j++; // * This is done so that the pointer moves forward by unity and allows for the pointer to be set at the start of string.

    for (;j<current_line->length();j++) {

        if (current_line->at(j) == '"') {
            ended = true;
        };

        if (current_line->at(j) == '"' || current_line->at(j) == ' ' || current_line->at(j) == '\n' || current_line->at(j) == ';') { // * The line/args ended.

            // * Our arg must be a num!
            // * Validate by isNan
            // * now generate the code for this.

            if (!ended) {

                if (skipIfError) return;

                delete pointer;
                delete current_line;

                std::cerr << "Expected \" after whatis statement. Found none\n"
                        << "At: " << *current_line << "\n";
                exit(COMPILER_ERR_WHATIS_MISSING_QUOTE);

            } else if (args.length() == 0) {

                if (skipIfError) return;

                delete pointer;
                delete current_line;

                std::cerr << "Expected an argument for the keyword whatis, Received None. \n"
                        << "At: " << *current_line << "\n";
                exit(COMPILER_ERR_WHATIS_MISSING_ARGUMENT);

            };

            break;

        };

        args += current_line->at(j);

    };

    internalSet = true;

    args = strip(args);
    
    std::transform(args.begin(),args.end(),args.begin(), [](unsigned char c) {
        return std::tolower(c);
    }); // * Lowercase args.

    internalVal = memory_pointer;

    if (args == "memorypointer") {

        internalSet = true;
        internalVal = memory_pointer;
        brainlite::set();
        internalSet = false;
        
        compiled_code.push_back(".");

    }

    argsCollectedLength = j;

}

void brainlite::end_loop(void) {

    /*
    Syntax:
    * Note: At end the memory pointer would be at looper's base address.
    * end -> marks end of loop (writes '-]' at end of code.
    */

   std::string code = "";

    if (isLooping) {
        isLooping = false;

        int moves_done = memory_pointer - looperAddress.back(); // * End the most recent loop (if nested loops)

        looperAddress.pop_back(); // eliminate the element

        bool backwards = (moves_done < 0); // current memory pointer is behind loop so bring front

        while (moves_done) {

            code += (backwards) ? ">" : "<";

            moves_done--;
        };

        memory_pointer -= moves_done; // move pointer according to moves.

        // refer to this example:

        /*
        
        moves done =  -3 => we need to send it 3 times forward. so memory pointer + 3.

        moves done = 3 => we need to send it 3 times backward. so memory pointer -3.
        
        */

       code += "-]";

       compiled_code.push_back(code);

    } else {
        delete pointer;
        delete current_line;

        std::cerr << "Found 'end' keyword without a corresponding loop.\n"
                << "At: " << *current_line << "\n";
        exit(COMPILER_ERR_END_LOOP_WITHOUT_START);
    }

};

inline void brainlite::out(void) noexcept{
    compiled_code.push_back(".");
}