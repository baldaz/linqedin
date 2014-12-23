#ifndef EXPERIENCE_H
#define EXPERIENCE_H

#include <string>

using std::string;

class Experience {
public:
    virtual ~Experience();
    virtual Experience* clone() const =0;
    virtual string print() const =0;
};

class Instruction : public Experience {
protected:
    string _location, _from, _to;
public:
    Instruction();
    Instruction(string, string, string);
    Instruction(const Instruction&);
    // ~Instruction();
    string location() const;
    string from() const;
    string to() const;
    void setLocation(string);
    void setFrom(string);
    void setTo(string);
    virtual Experience* clone() const;
    virtual string print() const;
};

class Work : public Instruction {
protected:
    string _description;
public:
    Work();
    Work(string, string, string, string);
    Work(const Work&);
    // ~Work();
    string description() const;
    void setDescription(string);
    virtual Experience* clone() const;
    virtual string print() const;
};

#endif