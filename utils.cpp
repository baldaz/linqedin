#include "utils.h"

std::string utilities::Utils::toLowerCase(std::string s) {
    for(unsigned int i = 0; i < s.size(); ++i)
        s[i] = std::tolower(s[i]);
    return s;
}

bool utilities::Utils::contains(std::vector<std::string> vec, std::string s) {
    bool found = false;
    if(!vec.empty()) {
        std::vector<std::string>::iterator it = vec.begin();
        for(; it < vec.end() && !found; ++it)
            if((*it) == s) found = true;
    }
    return found;
}