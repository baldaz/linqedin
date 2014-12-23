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
UserInfo::UserInfo(bool sx, QString n, QString s, QString b, QString e, QString a, QString t) :
                _sex(sx), _name(n), _surname(s), _birthdate(b), _email(e), _address(a), _telephon(t){}
UserInfo::UserInfo(const UserInfo& uf) :
                _sex(uf._sex), _name(uf._name), _surname(uf._surname),
                _birthdate(uf._birthdate), _email(uf._email), _address(uf._address),
                _telephon(uf._telephon), _skills(uf._skills), _exps(uf._exps) {}
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
QString UserInfo::name() const {
    return _name;
}
QString UserInfo::surname() const {
    return _surname;
}
QString UserInfo::birthdate() const {
    return _birthdate;
}
QString UserInfo::email() const {
    return _email;
}
QString UserInfo::address() const {
    return _address;
}
QString UserInfo::telephon() const {
    return _telephon;
}
bool UserInfo::sex() const {
    return _sex;
}
vector<QString> UserInfo::skills() const {
    return _skills;
}
vector<UserInfo::SmartExp> UserInfo::experience() const {
    return _exps;
}
vector<UserInfo::SmartExp> UserInfo::formations() const {
    return _formations;
}
void UserInfo::setName(QString n = "") {
    _name = n;
}
void UserInfo::setSurname(QString s = "") {
    _surname = s;
}
void UserInfo::setBirthdate(QString b = "") {
    _birthdate = b;
}
void UserInfo::setEmail(QString e = "") {
    _email = e;
}
void UserInfo::setTelephon(QString t = "") {
    _telephon = t;
}
void UserInfo::setAddress(QString a = "") {
    _address = a;
}
void UserInfo::setSex(bool s) {
    _sex = s;
}
void UserInfo::addSkill(QString newskill) {
    _skills.push_back(newskill);
}
void UserInfo::addExperience(Experience* newxp) {
    SmartExp s_exp(newxp);
    _exps.push_back(s_exp);
}
QString UserInfo::print() const {
    QString ret = "";
    QString sex = "";
    if(this->sex()) sex = "Maschio";
    else sex = "Femmina";
    ret += _name + " , " + _surname + " , " + sex + " , " + _address + " , " + _telephon + ", nato il " + _birthdate + "\n";
    ret += "E-mail >> " + _email + "\n";
    ret += "Personal skills >> ";
    for(int i = 0; i < _skills.size(); ++i)
        ret += _skills[i] + ", ";
    return ret;
}