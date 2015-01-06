#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

namespace utilities {
    class Utils {
    public:
       static std::string toLowerCase(std::string);
       static bool contains(std::vector<std::string>, std::string);
   };
}
#endif