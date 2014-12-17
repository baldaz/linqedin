#include "account.h"

Account::Account(Info* uf, Username* us, privLevel l = basic) : _info(uf), _user(us), _privilege(l) {}
Username* Account::getUsername() const {
    return _user;
}
Info* Account::getInfo() const {
    return _info;
}
void Account::setInfo(Info* uf) {
    _info = uf;
}