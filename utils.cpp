#include "utils.h"

std::string utilities::Utils::toLowerCase(std::string s) {
    for(unsigned int i = 0; i < s.size(); ++i)
        s[i] = std::tolower(s[i]);
    return s;
}

std::string utilities::Utils::levelToString(privLevel prl) {
    std::string ret = "";
    switch(prl) {
        case 0: ret = "Basic";
        break;
        case 1: ret = "Business";
        break;
        case 2: ret = "Executive";
        break;
        case 3: ret = "Root";
        break;
    }
    return ret;
}
bool utilities::Utils::contains(const std::vector<std::string>& vec, const std::string& s) {
    bool found = false;
    if(!vec.empty()) {
        std::vector<std::string>::const_iterator it = vec.begin();
        for(; it < vec.end() && !found; ++it)
            if((*it) == s) found = true;
    }
    return found;
}