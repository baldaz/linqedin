#include "account.h"

Account::Account(UserInfo* uf, Username* us) : _info(uf), _user(us){}
Username* Account::getUsername() const {
    return _user;
}
UserInfo* Account::getInfo() const {
    return _info;
}
void Account::setInfo(UserInfo* uf) {
    _info = uf;
}