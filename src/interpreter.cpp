#include "includes/interpreter.hpp"

void interpreterClass::exec_func(const char& tokenId, const std::unordered_map<char, std::function<void()>>& no_args) {

    auto find_fn = no_args.find(tokenId);

    if (find_fn != no_args.end()) {
        find_fn->second();
    };

};

void interpreter(std::string sourceFile) {

    interpreterClass ic;

    std::string line; // storage for lines

    std::string currentDir = std::filesystem::current_path();

    if (!std::filesystem::exists(currentDir+"/"+sourceFile)) {
        std::cerr << "Error: Cannot find the source file specified " << sourceFile << " at " << currentDir << std::endl;
        exit(1);
    };
    
    std::ifstream source(sourceFile);

    if (!source.is_open()) {
        std::cerr << "Error: Cannot read the source file specified " << sourceFile << " at " << currentDir << std::endl;
        exit(1);
    };

    while (std::getline(source,line)) {
        
        ic.source_code.push_back(line);

    };

    for(auto scode : ic.source_code) {
        ic.parse(scode);
        ic.line_no++;
    }


};

bool interpreterClass::validate(const char& token) {

    return validTokens.count(token);

}

void interpreterClass::parse(std::string line) {

    for (token_no = 0; token_no < line.length(); token_no++) {

        char token = line.at(token_no);

        //* Parse each character as a token
        
        if (!validate(token)) {
            std::cout << "Invalid token encountered!\n";
            exit(EXIT_FAILURE);
        }

        exec_func(token, execTokens);
        token_no += collectedArgsLength;

    }

};

interpreterClass::interpreterClass() {

    memory = (byte*) malloc( 38000 * sizeof(byte) ); // * Allocate brain's memory
    runtime_pointer = 0;
    isLooping = 0;
    line_no = 0;
    token_no = 0;
    collectedArgsLength = 0;

    validTokens.insert('+');
    validTokens.insert('-');
    validTokens.insert('>');
    validTokens.insert('<');
    validTokens.insert('[');
    validTokens.insert(']');
    validTokens.insert('.');
    validTokens.insert(',');

    execTokens['+'] = [this]() { this->inc(); };
    execTokens['-'] = [this]() { this->dec(); };
    execTokens['>'] = [this]() { this->right(); };
    execTokens['<'] = [this]() { this->left(); };
    execTokens['['] = [this]() { this->loop(); };
    execTokens[']'] = [this]() { this->end_loop(); };
    execTokens['.'] = [this]() { this->print(); };
    execTokens[','] = [this]() { this->input(); };
    
}

interpreterClass::~interpreterClass() {

    //delete runtime_pointer;
    free(memory);

}

void interpreterClass::inc(void) {

    this->memory[this->runtime_pointer]++;

}

void interpreterClass::dec(void) {

    this->memory[this->runtime_pointer]--;

}

void interpreterClass::print(void) {
    
    std::cout << static_cast<char>(this->memory[this->runtime_pointer]);

}

void interpreterClass::input(void) {

    char collector;

    std::cin >> collector;

    this->memory[this->runtime_pointer] = static_cast<int>(collector);

}

void interpreterClass::left(void) {

    this->runtime_pointer--;
    if (runtime_pointer < 0) {
        std::cerr << "Runtime pointer underflow!\n";
        exit(1);
    }

}

void interpreterClass::right(void) {
    
    this->runtime_pointer++;
    if (this->runtime_pointer > 37999) {
        std::cerr << "Runtime pointer overflow!\n";
        exit(1);
    }

}

void interpreterClass::loop(void) {

    isLooping++; //* Some loop has started.
    int start_Ptr = token_no+1;
    int end_Ptr = std::string::npos;

    /*
    
        * Assumptions:
        * Closing token ']' must lie in same line!

    */

    //* Validate loop ending:

    int bracket_count = 1;
    int end_Ptr = start_Ptr;
    
    while (end_Ptr < source_code.at(line_no).length() && bracket_count > 0) {
        char c = source_code.at(line_no).at(end_Ptr);
        if (c == '[') bracket_count++;
        else if (c == ']') bracket_count--;
        end_Ptr++;
    }

    if (bracket_count != 0) {
        std::cerr << "Loop not terminated!\n";
        exit(1);
    }

    /*

        * Loop ends if:
        * The condition is met -> the current runtime pointer is loop value
        * Note: token is at '['

    */

    std::string cut_part = source_code.at(line_no).substr(start_Ptr, end_Ptr - start_Ptr);

    while (memory[this->runtime_pointer] != 0) {
        
        for (char c : cut_part)
        interpreterClass::exec_func(c, execTokens);

    }

    collectedArgsLength = end_Ptr - start_Ptr + 1;
    interpreterClass::end_loop();

}

void interpreterClass::end_loop(void) {
    
    if (!isLooping) { //* Not even one loop is going on

        std::cerr << "Loop terminated without initalizing.\n";
        exit(1);

    }

    isLooping--;

}