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
        
        ic.parse(line);

    };


};

bool interpreterClass::validate(const char& token) {

    return validTokens.count(token);

}

void interpreterClass::parse(std::string line) {

    for (char token : line) {

        //* Parse each character as a token
        
        if (!validate(token)) {
            std::cout << "Invalid token encountered!\n";
            exit(EXIT_FAILURE);
        }

        exec_func(token, execTokens);

    }

};

interpreterClass::interpreterClass() {

    memory = (byte*) malloc( 38000 * sizeof(byte) ); // * Allocate brain's memory
    runtime_pointer = 0;
    isLooping = 0;

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

}

void interpreterClass::right(void) {

    this->runtime_pointer++;

}

void interpreterClass::loop(void) {

    isLooping++; //* Some loop has started.

    while (memory[this->runtime_pointer] != 0) {

        interpreterClass::exec_func();

        memory[this->runtime_pointer]--;

    }
      
    interpreterClass::end_loop();

}

void interpreterClass::end_loop(void) {
    
    if (!isLooping) { //* Not even one loop is going on

        std::cerr << "Loop terminated without initalizing.\n";
        exit(1);

    }

}