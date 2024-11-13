#pragma once

#include <iostream>

#include <vector>
#include <string>
#include <unordered_set>
#include <sstream>
#include <unordered_map>
#include <functional>
#include <cmath>
#include <algorithm>

int gcd(int nums[]);

class brainlite {

    private: //! Private

    int* pointer;
    bool looping;
    bool skipIfError;
    std::vector<std::string> lex; /* ! Current lexer code (UPDATED PER LINE) */
    std::vector<std::string> compiled_code; /* This code will be written to the output file */
    std::string* current_line;
    std::unordered_set<std::string> validTokens;

    /* Token skipped/ args collected */
    int argsCollectedLength;

    /* Mappers */
    std::unordered_map<std::string, std::function<void()>> execTokens;
    std::unordered_map<std::string, std::string> variables;

    /* For code */

    int memory_pointer;
    bool isLooping;

    bool internalSet;
    int internalVal;

    public: //! Public

    brainlite();
    ~brainlite();

    void lexCode(std::string line);
    int validate(std::string* token);
    void debug_tester(void);
    std::vector<std::string> getCode(void);
    int currentValue(void);

    /* Keyword functions */

    void set();
    void front(void);
    void back(void);
    void inc(void);
    void dec(void);
    void inctill(void);
    void dectill(void);
    void print(void);
    void input(void);
    void move(void);
    void loop(void);
    void whatis(void);
    void end_loop(void);

    /* Functional Map */

    void exec_func(const std::string& tokenId, const std::unordered_map<std::string, std::function<void()>>& no_args);

};