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
    pointer = new int(0);

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

    free(memory);
    delete pointer;

}

void interpreterClass::inc(void) {

    this->memory[this->pointer]++;

}

void interpreterClass::dec(void) {

    this->memory[this->pointer]--;

}

void interpreterClass::print(void) {

    std::cout << (char) this->memory[this->pointer];

}

void interpreterClass::input(void) {

    char collector;

    std::cin >> collector;

    this->memory[this->pointer] = (int) collector;   

}

void interpreterClass::left(void) {

    this->pointer--;

}

void interpreterClass::right(void) {

    this->pointer++;

}