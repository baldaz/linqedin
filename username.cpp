#include "username.h"
#include <QString>

Username::Username(QString l, QString p) : _login(l), _password(p) {}
Username::Username(const Username& usr) : _login(usr._login), _password(usr._password) {}
Username::~Username() {}
Username* Username::clone() const {
    return new Username(*this);
}
QString Username::login() const {
    return _login;
}
QString Username::password() const {
    return _password;
}
void Username::setLogin(QString l) {
    _login = l;
}
void Username::setPassword(QString p) {
    _password = p;
}
bool Username::operator==(const Username& usr) const {
    return ((usr._login == _login) && (usr._password == _password));
}