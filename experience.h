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
    Experience(const Experience&);
    Experience& operator=(const Experience&);
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

#endif
