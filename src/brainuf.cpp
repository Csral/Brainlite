#include "includes/brainuf.hpp"
#include "includes/errors.hpp"
#include "includes/utils.hpp"

void brainfuck::exec_func(const std::string& tokenId, const std::unordered_map<std::string, std::function<void()>>& no_args) {

    auto find_fn = no_args.find(tokenId);

    if (find_fn != no_args.end()) {
        find_fn->second();
    };

};

void brainfuck::debug_tester(void) {

    for (std::string code : compiled_code) {

        std::cout << code << std::endl;

    };

};

brainfuck::brainfuck() { // * Constructor

    pointer = new int(0); // ! Pointer starts at 0
    argsCollectedLength = 0;
    current_line = new std::string;
    memory_pointer = new int(0);

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
    execTokens["loop"] = [this]() { this->loop(); };
    execTokens["whatis"] = [this]() { this->whatis(); };
    execTokens["end"] = [this]() { this->end_loop(); };

};

brainfuck::~brainfuck() { // * Destructor
    delete pointer;  // Free dynamically allocated memory
    delete current_line;
    delete memory_pointer;
}

int brainfuck::validate(std::string* token) {

    if (token == nullptr) {

        std::stringstream err_msg;

        err_msg << "Unknown error occurred when validating the token " << *token << *current_line << "\n";

        throw interalError(err_msg.str());
    };

    return validTokens.count(*token);

};

void brainfuck::lexCode(std::string line) {

    *current_line = line;

    if (line.empty()) return;

    if (line.at(0) == '#') return; // ! Comment

    std::string collection = "";

    for (int i = 0; i < line.length(); i++) {

        *pointer = i;

        if (i+1 == line.length()) collection += line.at(i);

        if (line.at(i) == ' ' || line.at(i) == '\n' || i+1 == line.length() || line.at(i) == ';') { // * consider to obtain a token.

            if (collection.empty()) continue;

            if (!validate(&collection)) {
                // todo SYNTAX ERROR BY COUT.

                std::string errMsg = collection + " is not a valid keyword\nAt: " + line;

                delete pointer;
                delete current_line;
                delete memory_pointer;

                throw invalidToken(errMsg);
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

void brainfuck::set(void) {

    //! Return type: No. of characters read for input.

    std::string args = "";
    std::string code = ">++++[>";
    int toSet = 0;
    int j = (*pointer)+1;
    int looper = 0;

    int top = 0;
    int bottom = 0;

    for (;j<current_line->length();j++) {

        if (current_line->at(j) == ' ' || current_line->at(j) == '\n' || current_line->at(j) == ';') { // * The line/args ended.

            // * Our arg must be a num!
            // * Validate by isNan
            // * now generate the code for this.

            if (args.length() == 0) {
                std::stringstream err_msg;
                err_msg << "Expected an argument for the keyword set, Received None. \n" << "At: " << *current_line << "\n";

                delete pointer;
                delete current_line;
                delete memory_pointer;

                throw std::invalid_argument(err_msg.str());
            }

            break;

        };

        args += current_line->at(j);

    };

    // * now, find the best way to write a code for doing toSet using gcd.
    toSet = toInt(args);
    
    top = ceil(float(toSet)/4);
    bottom = floor(float(toSet)/4);

    while (looper < top) {

        code += "+";
        looper++;

    };

    code += "<-]>";

    while ((4*top - toSet) > 0) {

        code += '-';
        toSet++;
    
    };

    code += "<";

    // ! Logic: Loop 4 times with greatest of num/4 and then remove extra 4's form ceil.

    compiled_code.push_back(code);

    argsCollectedLength = j;

};

void brainfuck::front(void) {

    compiled_code.push_back(">");

};

void brainfuck::back(void) {

    compiled_code.push_back("<");

};

void brainfuck::inc(void) {

    //* Increases one bit

    compiled_code.push_back("+");

};


void brainfuck::dec(void) {

    //* Increases one bit

    compiled_code.push_back("-");

};

void brainfuck::inctill(void) {

    //* Increases n bit

    //! Return type: No. of characters read for input.

    std::string args = "";
    std::string code = "";
    int toSet = 0;
    int j = (*pointer)+1;
    int looper = 0;

    for (;j<current_line->length();j++) {

        if (current_line->at(j) == ' ' || current_line->at(j) == '\n' || current_line->at(j) == ';') { // * The line/args ended.

            // * Our arg must be a num!
            // * Validate by isNan
            // * now generate the code for this.

            if (args.length() == 0) {
                std::stringstream err_msg;
                err_msg << "Expected an argument for the keyword set, Received None. \n" << "At: " << *current_line << "\n";
                delete pointer;
                delete current_line;
                delete memory_pointer;
                throw std::invalid_argument(err_msg.str());
            }

            break;

        };

        args += current_line->at(j);

    };

    toSet = toInt(args);

    while (looper < toSet) {

        code += "+";
        looper++;

    };

    compiled_code.push_back(code);

    argsCollectedLength = j;

};

void brainfuck::dectill(void) {

    //* dec n bit

    //! Return type: No. of characters read for input.

    std::string args = "";
    std::string code = "";
    int toSet = 0;
    int j = (*pointer)+1;
    int looper = 0;

    for (;j<current_line->length();j++) {

        if (current_line->at(j) == ' ' || current_line->at(j) == '\n' || current_line->at(j) == ';') { // * The line/args ended.

            // * Our arg must be a num!
            // * Validate by isNan
            // * now generate the code for this.

            if (args.length() == 0) {
                std::stringstream err_msg;
                err_msg << "Expected an argument for the keyword set, Received None. \n" << "At: " << *current_line << "\n";
                delete pointer;
                delete current_line;
                delete memory_pointer;
                throw std::invalid_argument(err_msg.str());
            }

            break;

        };

        args += current_line->at(j);

    };

    toSet = toInt(args);

    while (looper < toSet) {

        code += "-";
        looper++;

    };

    compiled_code.push_back(code);

    argsCollectedLength = j;

};


void brainfuck::move(void) {

    //* move n bit

    //! Return type: No. of characters read for input.

    std::string args = "";
    std::string code = "";
    int toMove = 0;
    int j = (*pointer)+1;
    int looper = 0;

    int top = 0;
    int bottom = 0;

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
                std::stringstream err_msg;
                err_msg << "Expected an argument for the keyword set, Received None. \n" << "At: " << *current_line << "\n";
                delete pointer;
                delete current_line;
                delete memory_pointer;
                throw std::invalid_argument(err_msg.str());
            }

            break;

        };

        args += current_line->at(j);

    };

    toMove = toInt(args);

    while (looper < toMove) {

        code += (backwards) ? "<" : ">";
        looper++;

    };

    compiled_code.push_back(code);

    argsCollectedLength = j;

};

void brainfuck::print(void) {

};

void brainfuck::loop(void) {

}

void brainfuck::whatis(void) {

}

void brainfuck::end_loop(void) {

    /*
    Syntax:
    *    loop (how many times ; current/higher/lower)  things to do in loop end
    * current/higher/lower -> current is denoted by 0. Current memory address/pointer is used as looper.
    * higher is denoted by 1, it means to use next memory address as the looper
    * lower means to use the memory address behind as looper
    * end -> marks end of loop (writes '-]' at end of code.
    */

    if (isLooping) {
        isLooping = false;
    };

};