#include "account.h"

Account::Account(Info* uf, Username* us) : _info(uf), _user(us){}
Username* Account::getUsername() const {
    return _user;
}
Info* Account::getInfo() const {
    return _info;
}
void Account::setInfo(Info* uf) {
    _info = uf;
}