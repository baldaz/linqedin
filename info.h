#ifndef INFO_H
#define INFO_H

#include <string>
#include <sstream>
#include <vector>
#include "experience.h"
#include "smartptr.h"

using std::vector;
using std::string;

class Info {
public:
    virtual ~Info();
    virtual Info* clone() const =0;
    virtual string print() const =0;
    virtual string printHtml() const =0;
};

class UserInfo : public Info {
private:
    bool _sex;
    string _name, _surname, _birthdate, _email, _address, _telephon, _website;
    vector<string> _languages, _skills, _interests;
    vector<SmartPtr<Experience> > _formations;
    vector<SmartPtr<Experience> > _exps;
public:
    UserInfo();
    UserInfo(bool, string, string, string, string, string, string, string);
    UserInfo(const UserInfo&);
    Info* clone() const;
    // virtual ~UserInfo();
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
    vector<SmartPtr<Experience> > experience() const;
    vector<SmartPtr<Experience> > formations() const;
    void setSex(bool);
    void setName(string);
    void setSurname(string);
    void setBirthdate(string);
    void setEmail(string);
    void setAddress(string);
    void setTelephon(string);
    void setWebsite(string);
    void addLanguage(string);
    void addSkill(string);
    void addInterest(string);
    void addExperience(Experience*);
    void addFormation(Experience*);
    int age() const;
    virtual string print() const;
    virtual string printHtml() const;
};

#endif