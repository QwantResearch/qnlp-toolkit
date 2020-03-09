#ifndef QNLP_UTILS_H
#define QNLP_UTILS_H
#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <regex>
#include "utf8/utf8.h"
#include <algorithm> 
#include <chrono> 
// #include <boost/algorithm/string.hpp>

// void Trim(std::string& s);

namespace qnlp {

void Split(const std::string& line, std::vector<std::string>& pieces, const std::string del=" ");

std::string Join(const std::vector<std::string>& words, const std::string del=" ");

bool EndsWith(std::string const &fullString, std::string const suffix);

// std::string E        scapeRegex(std::string text);

char ToLower(char& c);
unsigned char  ToLower(unsigned char& c);
unsigned short  ToLower(unsigned short& c);
unsigned int  ToLower(unsigned int& c);

};

#endif // QNLP_UTILS_H
