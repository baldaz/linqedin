#include "username.h"

Username::Username(string l, string p) : login(l), password(p){}
string Username::getLogin() const {
    return login;
}
string Username::getPassword() const {
    return password;
}
void Username::setLogin(string l) {
    login = l;
}
void Username::setPassword(string p) {
    password = p;
}