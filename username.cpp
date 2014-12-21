#include "username.h"
#include <QString>

Username::Username(QString l = "", QString p = "") : _login(l), _password(p){}
Username::~Username() {}
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
    return (usr._login == _login) && (usr._password == _password);
}