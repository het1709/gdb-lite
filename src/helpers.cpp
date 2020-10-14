#include <vector>
#include <string>
#include <sstream>

#include "helpers.hpp"

// Splits a string into various substrings using a given delimiter
std::vector<std::string> split(const std::string &s, char delimiter) {
    std::vector<std::string> out{};
    std::stringstream ss{s};
    std::string item;

    while (std::getline(ss, item, delimiter)) {
        out.push_back(item);
    }

    return out;
}

// Checks to see if s1 is a prefix string of s2
bool is_prefix(const std::string& s1, const std::string& s2) {
    if (s1.size() > s2.size()) return false;
    return std::equal(s1.begin(), s1.end(), s2.begin());
}

// Converts str to lower case
void to_lower(std::string& str) {
    for (int i = 0; i < str.length(); i++) {
        str[i] = tolower(str[i]);
    }
}

std::string& ltrim(std::string& str, const std::string& chars )
{
    str.erase(0, str.find_first_not_of(chars));
    return str;
}
 
std::string& rtrim(std::string& str, const std::string& chars )
{
    str.erase(str.find_last_not_of(chars) + 1);
    return str;
}
 
std::string& trim(std::string& str, const std::string& chars )
{
    return ltrim(rtrim(str, chars), chars);
}