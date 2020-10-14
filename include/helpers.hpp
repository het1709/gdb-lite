#ifndef GDBLITE_HELPERS_H
#define GDBLITE_HELPERS_H

#include <vector>

std::vector<std::string> split(const std::string &s, char delimiter);

bool is_prefix(const std::string& s, const std::string& of);

void to_lower(std::string& str);

std::string& ltrim(std::string& str, const std::string& chars = "\t\n\v\f\r ");

std::string& rtrim(std::string& str, const std::string& chars = "\t\n\v\f\r ");

std::string& trim(std::string& str, const std::string& chars = "\t\n\v\f\r ");

#endif