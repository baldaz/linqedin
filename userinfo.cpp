#include "userinfo.h"

UserInfo::UserInfo(string n, string s, string b, string e, string t) :
                _name(n), _surname(s), _birthdate(b), _email(e), _telephon(t){}
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
string UserInfo::getTelephon() const {
    return _telephon;
}
void UserInfo::setName(string n) {
    _name = n;
}
void UserInfo::setSurname(string s) {
    _surname = s;
}
void UserInfo::setBirthdate(string b) {
    _birthdate = b;
}
void UserInfo::setEmail(string e) {
    _email = e;
}
void UserInfo::setTelephon(string t) {
    _telephon = t;
}