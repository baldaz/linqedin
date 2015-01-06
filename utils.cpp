#include "utils.h"

std::string utilities::Utils::toLowerCase(std::string s) {
    for(unsigned int i = 0; i < s.size(); ++i)
        s[i] = std::tolower(s[i]);
    return s;
}