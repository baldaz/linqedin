#include "username.h"

Username::Username(string l, string p) : _login(l), _password(p){}
string Username::getLogin() const {
    return _login;
}
string Username::getPassword() const {
    return _password;
}
void Username::setLogin(string l) {
    _login = l;
}
void Username::setPassword(string p) {
    _password = p;
}