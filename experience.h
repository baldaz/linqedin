#ifndef EXPERIENCE_H
#define EXPERIENCE_H

#include <string>
#include <QDate>

using std::string;

class Experience {
private:
    int _type;
    string _location, _role;
    QDate _from, _to;
public:
    Experience(int = 0, const string& ="", const string& ="", const QDate& = QDate::currentDate(), const QDate& = QDate::currentDate());
    // Experience(const Experience&);
    // Experience& operator=(const Experience&);
	bool operator==(const Experience&) const;
    int type() const;
    void setType(int);
    string location() const;
    void setLocation(const string&);
    string role() const;
    void setRole(const string&);
    QDate from() const;
    void setFrom(const QDate&);
    QDate to() const;
    void setTo(const QDate&);
};

// class Experience {
// public:
//     virtual ~Experience();
//     virtual Experience* clone() const =0;
//     virtual string print() const =0;
// };

// class Instruction : public Experience {
// protected:
//     string _location, _from, _to;
// public:
//     Instruction();
//     Instruction(const string&, const string&, const string&);
//     Instruction(const Instruction&);
//     // ~Instruction();
//     const string& location() const;
//     const string& from() const;
//     const string& to() const;
//     void setLocation(const string&);
//     void setFrom(const string&);
//     void setTo(const string&);
//     virtual Experience* clone() const;
//     virtual string print() const;
// };

// class Work : public Instruction {
// protected:
//     string _description;
// public:
//     Work();
//     Work(const string&, const string&, const string&, const string&);
//     Work(const Work&);
//     // ~Work();
//     const string& description() const;
//     void setDescription(const string&);
//     virtual Experience* clone() const;
//     virtual string print() const;
// };

#endif
