#include "info.h"

Info::~Info() {}
UserInfo::UserInfo() {}
UserInfo::UserInfo(bool sx, string n, string s, string b, string e, string a, string t) :
                _sex(sx), _name(n), _surname(s), _birthdate(b), _email(e), _address(a), _telephon(t){}
string UserInfo::getName() const {
    return _name;
}
string UserInfo::getSurname() const {
    return _surname;
}
string UserInfo::getBirthdate() const {
    return _birthdate;
}
string UserInfo::getEmail() const {
    return _email;
}
string UserInfo::getAddress() const {
    return _address;
}
string UserInfo::getTelephon() const {
    return _telephon;
}
string UserInfo::getSex() const {
    if(_sex) return "Maschio";
    else return "Femmina";
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
string UserInfo::print() const {
    string ret ="";
    ret += _name + " : " + _surname + " : " + this->getSex() + " : " + _address + " : " + _telephon;
    return ret;
}