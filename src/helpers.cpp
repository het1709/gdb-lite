#include <vector>
#include <string>
#include <sstream>

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