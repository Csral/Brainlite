#pragma once

#include <vector>
#include <string>
#include <unordered_set>
#include <sstream>
#include <unordered_map>
#include <functional>

int gcd(int nums[]);

std::unordered_set<std::string> validTokens = {
        "set",
        "move",
        "front", "right"
};

std::unordered_map<std::string,int> type_mapper = {

    {
        "num",
        0
    },
    {
        "str",
        1
    },
    {
        "bool",
        2
    }

};

std::unordered_map<std::string, std::unordered_map<std::string,std::string>> tokens = {
    {
        "set", // token as key
        {
            {"args","yes"},
            {"type","num"}
        }
    },
    {
        "move",
        {
            {"args","yes"},
            {"type","num"}
        }
    }
};

class brainfuck {

    private: //! Private

    int* pointer;
    bool looping;
    std::vector<std::string> lex; /* ! Current lexer code (UPDATED PER LINE) */
    std::vector<std::string> compiled_code; /* This code will be written to the output file */
    std::string* current_line;

    /* Token skipped/ args collected */
    int argsCollectedLength;

    /* Mappers */
    std::unordered_map<std::string, std::function<void()>> execTokens;

    /* For code */

    int* memory_pointer;
    bool isLooping;

    public: //! Public

    brainfuck();
    void lexCode(std::string line);
    int validate(std::string* token);
    std::vector<int> brainfuck::tokenInfo(std::string* token);

    /* Keyword functions */

    void set(void);
    void front(void);
    void back(void);
    void inc(void);
    void dec(void);
    void inctill(void);
    void dectill(void);
    void print(void);
    void move(void);
    void loop(void);
    void whatis(void);
    void end_loop(void);

    /* Functional Map */

    void exec_func(const std::string& tokenId, const std::unordered_map<std::string, std::function<void()>>& no_args);

};