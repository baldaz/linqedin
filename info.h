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
protected:
    bool _sex;
    string _name, _surname, _birthdate, _email, _address, _telephon, _website;
    vector<string> _languages, _skills, _interests;
    vector<SmartPtr<Experience> > _formations;
    vector<SmartPtr<Experience> > _exps;
public:
    UserInfo();
    UserInfo(bool, const string&, const string&, const string&, const string&, const string&, const string&, const string&);
    UserInfo(const UserInfo&);
    Info* clone() const;
    // virtual ~UserInfo();
    UserInfo& operator=(const UserInfo&);
    const string& name() const;
    const string& surname() const;
    const string& birthdate() const;
    const string& email() const;
    const string& address() const;
    const string& telephon() const;
    const string& website() const;
    bool sex() const;
    vector<string> languages() const;
    vector<string> skills() const;
    vector<string> interests() const;
    vector<SmartPtr<Experience> > experience() const;
    vector<SmartPtr<Experience> > formations() const;
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
    void addExperience(Experience*);
    void addFormation(Experience*);
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
    Info* clone() const;
    const string& bio() const;
    void setBio(const string&);
    virtual string print() const;
    virtual string printHtml() const;
};
#endif