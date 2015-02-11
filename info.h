#ifndef INFO_H
#define INFO_H

#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <QDate>
#include "experience.h"
#include "smartptr.h"
#include "error.h"

using std::vector;
using std::list;
using std::string;

class Dispatcher;

class Info {
public:
    virtual ~Info();
    virtual Info* clone() const =0;
    virtual string print() const =0;
    virtual string dispatch(const Dispatcher&) const =0;
};

class UserInfo : public Info {
private:
    string _name, _surname, _email, _address, _telephon, _website;
    vector<string> _languages, _skills, _interests;
    list<Experience*> _exp;
    QDate _birthdate;
public:
    UserInfo(const string& ="", const string& ="", const string& ="", const string& ="", const string& ="", const string& ="", const QDate& bb = QDate::currentDate());
    UserInfo(const UserInfo&);
    virtual ~UserInfo();
    Info* clone() const;
    UserInfo& operator=(const UserInfo&);
    QDate birthdate() const;
    string name() const;
    string surname() const;
    string email() const;
    string address() const;
    string telephon() const;
    string website() const;
    vector<string> languages() const;
    vector<string> skills() const;
    vector<string> interests() const;
    list<Experience*> experiences() const;
    Experience* lastExperience() const;
    void setName(const string&);
    void setSurname(const string&);
    void setBirthdate(const QDate&) throw(Error);
    void setEmail(const string&);
    void setAddress(const string&);
    void setTelephon(const string&);
    void setWebsite(const string&);
    void addLanguage(const string&);
    void removeLanguage(const string&);
    void addSkill(const string&);
    void removeSkill(const string&);
    void addInterest(const string&);
    void removeInterest(const string&);
    void addExperience(const Experience&);
    void removeExperience(const Experience&);
    int age() const;
    virtual string print() const;
    virtual string dispatch(const Dispatcher&) const;
};

class Bio : public UserInfo {
private:
    string _bio;
public:
    Bio(const string& = "", const string& = "", const string& = "", const string& = "", const string& = "", const string& = "",  const QDate& = QDate::currentDate(), const string& = "");
    Bio(const Bio&);
    virtual ~Bio();
    Info* clone() const;
    const string& bio() const;
    void setBio(const string&);
    virtual string print() const;
    virtual string dispatch(const Dispatcher&) const;
};
#endif
