#ifndef INFO_H
#define INFO_H

#include <string>
#include <sstream>
#include <vector>
#include <list>
#include "experience.h"
#include "smartptr.h"

using std::vector;
using std::list;
using std::string;

class Info {
public:
    virtual ~Info();
    virtual Info* clone() const =0;
    virtual string print() const =0;
    virtual string printHtml() const =0;
};

class UserInfo : public Info {
protected:
    bool _sex;
    string _name, _surname, _birthdate, _email, _address, _telephon, _website;
    vector<string> _languages, _skills, _interests;
    list<Experience> _exp;
public:
    // UserInfo();
    UserInfo(bool = false, const string& ="", const string& ="", const string& ="", const string& ="", const string& ="", const string& ="", const string& ="");
    UserInfo(const UserInfo&);
    virtual ~UserInfo();
    Info* clone() const;
    UserInfo& operator=(const UserInfo&);
    string name() const;
    string surname() const;
    string birthdate() const;
    string email() const;
    string address() const;
    string telephon() const;
    string website() const;
    bool sex() const;
    vector<string> languages() const;
    vector<string> skills() const;
    vector<string> interests() const;
    list<Experience> experiences() const;
    void setSex(bool);
    void setName(const string&);
    void setSurname(const string&);
    void setBirthdate(const string&);
    void setEmail(const string&);
    void setAddress(const string&);
    void setTelephon(const string&);
    void setWebsite(const string&);
    void addLanguage(const string&);
    void addSkill(const string&);
    void addInterest(const string&);
    void addExperience(const Experience&);
    int age() const;
    virtual string print() const;
    virtual string printHtml() const;
};

class Bio : public UserInfo {
protected:
    string _bio;
public:
    Bio(bool, const string&, const string&, const string&, const string&, const string&, const string&, const string&, const string&);
    Bio(const Bio&);
    virtual ~Bio();
    Info* clone() const;
    const string& bio() const;
    void setBio(const string&);
    virtual string print() const;
    virtual string printHtml() const;
};
#endif