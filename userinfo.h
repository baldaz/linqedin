#ifndef USERINFO_H
#define USERINFO_H

#include <string>
#include <vector>
#include "experience.h"

using std::string;
using std::vector;

class UserInfo {
private:
    bool _sex;
    string _name, _surname, _birthdate, _email, _address, _telephon;
    vector<string> _skills;
    vector<Experience*> _formations;
    vector<Experience*> _exps;
public:
    UserInfo(bool, string, string, string, string, string, string);
    string getName() const;
    string getSurname() const;
    string getBirthdate() const;
    string getEmail() const;
    string getAddress() const;
    string getTelephon() const;
    string getSex() const;
    vector<string>* getSkills() const;
    vector<Experience*> getFormations() const;
    vector<Experience*> getExperiences() const;
    void setSex(bool) const;
    void setName(string);
    void setSurname(string);
    void setBirthdate(string);
    void setEmail(string);
    void setAddress(string);
    void setTelephon(string);
    void addSkill(string);
    void addFormation(Experience*);
    void addExperience(Experience*);
};
#endif