#ifndef USERINFO_H
#define USERINFO_H

#include <string>
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
};

class UserInfo : public Info {
private:
    class SmartExp {
    private:
        Experience *ptr;
    public:
        SmartExp(Experience*);
        SmartExp(const SmartExp&);
        SmartExp& operator=(const SmartExp&);
        ~SmartExp();
        Experience& operator*() const;
        Experience* operator->() const;
    };

    bool _sex;
    string _name, _surname, _birthdate, _email, _address, _telephon, _website;
    vector<string> _skills, _interests;
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
    void addSkill(string);
    void addInterest(string);
    void addExperience(Experience*);
    void addFormation(Experience*);
    virtual string print() const;
};

#endif