#ifndef QNLP_UTILS_H
#define QNLP_UTILS_H
#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <regex>
// #include <boost/algorithm/string.hpp>

// void Trim(std::string& s);

namespace qnlp {

void Split(const std::string& line, std::vector<std::string>& pieces, const std::string del=" ");

std::string Join(const std::vector<std::string>& words, const std::string del=" ");

bool EndsWith(std::string const &fullString, std::string const suffix);

// std::string E        scapeRegex(std::string text);

};

#endif // QNLP_UTILS_H
