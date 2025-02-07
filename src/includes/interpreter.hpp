#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <malloc.h>
#include <unordered_set>
#include <unordered_map>
#include <functional>

typedef unsigned char byte;

void interpreter(std::string sourceFile);

class interpreterClass {

    private:
    byte* memory;
    int runtime_pointer;
    int isLooping;
    std::unordered_set<char> validTokens;

    /* Mappers */
    
    std::unordered_map<char, std::function<void()>> execTokens;

    public:

    interpreterClass();
    ~interpreterClass();

    void exec_func(const char& tokenId, const std::unordered_map<char, std::function<void()>>& no_args);

    /* Internal functions */

    void parse(std::string line);
    bool validate(const char& token);

    /* Keyword functions */

    void inc(void);
    void dec(void);
    void loop(void);
    void end_loop(void);
    void print(void);
    void input(void);
    void right(void);
    void left(void);

};