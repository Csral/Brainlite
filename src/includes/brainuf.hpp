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

#pragma once
#ifndef __BRAINLITE_COMPILER_INCLUDED__
#define __BRAINLITE_COMPILER_INCLUDED__

#include <iostream>

#include <vector>
#include <string>
#include <unordered_set>
#include <sstream>
#include <unordered_map>
#include <functional>
#include <cmath>
#include <algorithm>
#include <stdint.h>

class brainlite {

    private: //! Private

    uint64_t* pointer;
    bool skipIfError;
    std::vector<std::string> lex; /* ! Current lexer code (UPDATED PER LINE) */
    std::vector<std::string> compiled_code; /* This code will be written to the output file */
    std::string* current_line;
    std::unordered_set<std::string> validTokens;

    /* Token skipped/ args collected */
    uint64_t argsCollectedLength;

    /* Mappers */
    std::unordered_map<std::string, std::function<void()>> execTokens;
    std::unordered_map<std::string, std::string> variables;

    /* For code */

    int memory_pointer;
    bool isLooping;

    bool internalSet;
    int internalVal;

    std::vector<int> looperAddress; // base address of looping. So memory_pointer - looperAddress = number of shifts in memory. 

    public: //! Public

    brainlite();
    ~brainlite();

    void lexCode(std::string line);
    int validate(const std::string& token);
    void debug_tester(void);
    std::vector<std::string> getCode(void);
    int currentValue(void);

    /* Keyword functions */

    void set(void);
    void front(void);
    void back(void);
    inline void inc(void) noexcept;
    inline void dec(void) noexcept;
    void inctill(void);
    void dectill(void);
    void print(void);
    void input(void);
    void move(void);
    void loop(void);
    void whatis(void);
    void end_loop(void);
    inline void out(void) noexcept;

    /* Functional Map */

    void exec_func(const std::string& tokenId, const std::unordered_map<std::string, std::function<void()>>& no_args);

};

#endif