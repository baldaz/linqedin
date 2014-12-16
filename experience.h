#ifndef EXPERIENCE_H
#define EXPERIENCE_H

#include <string>

using std::string;

class Experience {
private:
    string _location, _description, _from, _to;
public:
    Experience(string, string, string, string, string);
    string getLocation() const;
    string getDescription() const;
    string getFrom() const;
    string getTo() const;
    void setLocation(string);
    void setDescription(string);
    void setFrom(string);
    void setTo(string);
};
#endif