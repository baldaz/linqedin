#include "info.h"

Info::~Info() {}
UserInfo::UserInfo() {}
UserInfo::UserInfo(bool sx, QString n, QString s, QString b, QString e, QString a, QString t) :
                _sex(sx), _name(n), _surname(s), _birthdate(b), _email(e), _address(a), _telephon(t){}
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
QString UserInfo::sex() const {
    if(_sex) return "Maschio";
    else return "Femmina";
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
QString UserInfo::print() const {
    QString ret ="";
    ret += _name + " : " + _surname + " : " + this->sex() + " : " + _address + " : " + _telephon;
    return ret;
}