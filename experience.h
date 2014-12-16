#ifndef EXPERIENCE_H
#define EXPERIENCE_H

#include <string>

using std::string;

class Experience {
private:
    string _location, _description, _from, _to;
public:
    Experience(string, string, string, string, string);
};
#endif