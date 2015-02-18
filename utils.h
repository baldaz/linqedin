#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include "privlevel.h"

// Namespace minimale per le funzioni di utilita'

namespace utilities {
    class Utils {
    public:
       static std::string toLowerCase(std::string);
       static bool contains(const std::vector<std::string>&, const std::string&);
   };
}
#endif