#pragma once

#include <stdexcept>
#include <exception>
#include <string>
#include <sstream>

int toInt(const std::string& num);
int ascii(const char& letter);
int ringBuffer(const int& number);
bool endQuestionMark(const std::string& str);
std::string strip(const std::string& str, const char& reference = ' ', const std::string& replace = "");