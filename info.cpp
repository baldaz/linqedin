#include "info.h"

UserInfo::SmartExp::SmartExp(Experience* exp) : ptr(exp->clone()) {}
UserInfo::SmartExp::SmartExp(const SmartExp& sm_exp) : ptr((sm_exp.ptr)->clone()) {}
UserInfo::SmartExp& UserInfo::SmartExp::operator=(const SmartExp& sm_exp) {
    if(this != &sm_exp) {
        delete ptr;
        ptr = (sm_exp.ptr)->clone();
    }
    return *this;
}
UserInfo::SmartExp::~SmartExp() { delete ptr; }

Info::~Info() {}
UserInfo::UserInfo() {}
UserInfo::UserInfo(bool sx, string n, string s, string b, string e, string a, string t, string w) :
                _sex(sx), _name(n), _surname(s), _birthdate(b), _email(e), _address(a), _telephon(t), _website(w){}
UserInfo::UserInfo(const UserInfo& uf) :
                _sex(uf._sex), _name(uf._name), _surname(uf._surname),_birthdate(uf._birthdate),
                _email(uf._email), _address(uf._address), _telephon(uf._telephon), _skills(uf._skills),
                _exps(uf._exps), _interests(uf._interests), _website(uf._website) {}
UserInfo& UserInfo::operator=(const UserInfo& uif) {
    if(this != &uif) {
        _name = uif._name;
        _surname = uif._surname;
        _birthdate = uif._birthdate;
        _address = uif._address;
        _email = uif._email;
        _telephon = uif._telephon;
        _sex = uif._sex;
    }
    return *this;
}
Info* UserInfo::clone() const {
    return new UserInfo(*this);
}
string UserInfo::name() const {
    return _name;
}
string UserInfo::surname() const {
    return _surname;
}
string UserInfo::birthdate() const {
    return _birthdate;
}
string UserInfo::email() const {
    return _email;
}
string UserInfo::address() const {
    return _address;
}
string UserInfo::telephon() const {
    return _telephon;
}
bool UserInfo::sex() const {
    return _sex;
}
string UserInfo::website() const {
    return _website;
}
vector<string> UserInfo::skills() const {
    return _skills;
}
vector<string> UserInfo::interests() const {
    return _interests;
}
vector<UserInfo::SmartExp> UserInfo::experience() const {
    return _exps;
}
vector<UserInfo::SmartExp> UserInfo::formations() const {
    return _formations;
}
void UserInfo::setName(string n = "") {
    _name = n;
}
void UserInfo::setSurname(string s = "") {
    _surname = s;
}
void UserInfo::setBirthdate(string b = "") {
    _birthdate = b;
}
void UserInfo::setEmail(string e = "") {
    _email = e;
}
void UserInfo::setTelephon(string t = "") {
    _telephon = t;
}
void UserInfo::setAddress(string a = "") {
    _address = a;
}
void UserInfo::setSex(bool s) {
    _sex = s;
}
void UserInfo::setWebsite(string site) {
    _website = site;
}
void UserInfo::addSkill(string newskill) {
    _skills.push_back(newskill);
}
void UserInfo::addInterest(string newinterest) {
    _interests.push_back(newinterest);
}
void UserInfo::addExperience(Experience* newxp) {
    SmartExp s_exp(newxp);
    _exps.push_back(s_exp);
}
string UserInfo::print() const {
    string ret = "";
    string sex = "";
    if(this->sex()) sex = "Maschio";
    else sex = "Femmina";
    ret += _name + " , " + _surname + " , " + sex + " , " + _address + " , " + _telephon + ", nato il " + _birthdate + "\n";
    ret += "E-mail >> " + _email + " Sito web >> " + _website + "\n";
    ret += "Personal interests >> ";
    for(int i = 0; i < _interests.size(); ++i)
        ret += _interests[i] + ", ";
    ret += "\nPersonal skills >> ";
    for(int i = 0; i < _skills.size(); ++i)
        ret += _skills[i] + ", ";
    return ret;
}