#pragma once

#ifndef __BRAINLITE_INTERPRETER_INCLUDED__
#define __BRAINLITE_INTERPRETER_INCLUDED__

#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <malloc.h>
#include <unordered_set>
#include <unordered_map>
#include <functional>
#include <algorithm>
#include <stdint.h>

#include "errors.hpp"

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

    inline void inc(void) noexcept;
    inline void dec(void) noexcept;
    void loop(void);
    void end_loop(void);
    inline void print(void) noexcept;
    void input(void) noexcept;
    void right(void);
    void left(void);

    /* Source Handlers */
    std::vector<std::string> source_code;
    int line_no;
    uint32_t token_no;
    int collectedArgsLength;

};

#endif