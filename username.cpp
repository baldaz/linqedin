#include "username.h"

Username::Username(string l = "", string p = "") : _login(l), _password(p) {}
string Username::login() const {
    return _login;
}
string Username::password() const {
    return _password;
}
void Username::setLogin(string l) {
    _login = l;
}
void Username::setPassword(string p) {
    _password = p;
}
bool Username::operator==(const Username& usr) const {
    return ((usr._login == _login) && (usr._password == _password));
}