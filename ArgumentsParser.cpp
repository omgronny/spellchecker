
#include <optional>
#include "ArgumentsParser.h"

std::pair<size_t, bool> ArgumentsParser::parse_input(std::string &s) {
    auto pos = s.find('=');

    if (pos >= s.size()) {
        throw std::exception();
    }

    size_t number = std::stoi(s.substr(pos + 1, s.size() - 1));
    return {number, s[1] == 'n'};
}
