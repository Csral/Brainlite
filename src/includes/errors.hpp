#pragma once

#include <stdexcept>
#include <exception>

class syntaxError : public std::runtime_error {

    public:

    syntaxError(const std::string& message) : std::runtime_error(message) {};

};

class invalidToken : public std::runtime_error {

    public:

    invalidToken(const std::string& message) : std::runtime_error(message) {};

};

class interalError : public std::runtime_error {

    public:

    interalError(const std::string& message) : std::runtime_error(message) {};

};

class argsError : public std::runtime_error {

    public:

    argsError(const std::string& message) : std::runtime_error(message) {};

};