#include "account.h"

Account::Account() {}
Account::Account(Info* uf, Username* us, privLevel l = basic) : _info(uf), _user(us), _privilege(l) {}
Account::Account(const Account& acc) : _info(acc._info), _user(acc._user), _privilege(acc._privilege) /*_info(acc._info->clone()), _user(acc._user->clone()), _privilege(acc._privilege)*/ {}
Account::~Account() { delete _user; delete _info;}
Account* Account::clone() const {
    return new Account(*this);
}
Account& Account::operator=(const Account& acc) {
    if(this != &acc) {
        delete _info;
        delete _user;
        _info = acc._info;
        _user = acc._user;
    }
    return *this;
}
Username* Account::username() const {
    return _user;
}
Info* Account::info() const {
    return _info;
}
privLevel Account::prLevel() const {
    return _privilege;
}
void Account::setInfo(Info* uf) {
    _info = uf;
}
void Account::setPrLevel(privLevel newlevel) {
    _privilege = newlevel;
}