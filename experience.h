#ifndef EXPERIENCE_H
#define EXPERIENCE_H

#include <string>

using std::string;

class Experience {
    virtual ~Experience();
    virtual string print() const =0;
};

class Instruction : public Experience {
protected:
    string _location, _from, _to;
public:
    Instruction();
    Instruction(string, string, string);
    virtual ~Instruction();
    string getLocation() const;
    string getFrom() const;
    string getTo() const;
    void setLocation(string);
    void setFrom(string);
    void setTo(string);
    virtual string print() const;
};

class Work : public Instruction {
protected:
    string _description;
public:
    Work();
    Work(string, string, string, string);
    virtual ~Work();
    string getDescription() const;
    void setDescription(string);
    virtual string print() const;
};

#endif