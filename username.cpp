#include "username.h"

Username::Username(const string& l, const string& p) : _login(l), _password(p) {}
// Username::Username(const Username& usr) : _login(usr._login), _password(usr._password) {}
// Username* Username::clone() const {
//     return new Username(*this);
// }
const string& Username::login() const {
    return _login;
}
const string& Username::password() const {
    return _password;
}
void Username::setLogin(const string& l) {
    _login = l;
}
void Username::setPassword(const string& p) {
    _password = p;
}
bool Username::operator==(const Username& usr) const {
    return ((usr._login == _login) && (usr._password == _password));
}
bool Username::operator!=(const Username& usr) const {
    return ((usr._login != _login) || (usr._password != _password));
}