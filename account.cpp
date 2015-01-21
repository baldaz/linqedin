#include "account.h"

// Account::Account() {}
Account::Account(Info* uf, const Username& us, privLevel l = basic) : _info(uf->clone()), _user(us), _privilege(l) {}
Account::Account(const Account& acc) : /* _info(acc._info), _user(acc._user), _privilege(acc._privilege)*/ _info(acc._info->clone()), _user(acc._user), _history(acc._history), _privilege(acc._privilege) {}
Account::~Account() {delete _info;}
Account* Account::clone() const {
    return new Account(*this);
}
Account& Account::operator=(const Account& acc) {
    if(this != &acc) {
        delete _info;
        _info = acc._info->clone();
        _user = acc._user;
        _privilege = acc._privilege;
    }
    return *this;
}
Username Account::username() const {
    return _user;
}
Info* Account::info() const {
    return _info;
}
privLevel Account::prLevel() const {
    return _privilege;
}
void Account::setInfo(Info* uf) {
    if(_info) delete _info;
    _info = uf;
}
void Account::setPrLevel(privLevel newlevel) {
    _privilege = newlevel;
}
vector<SmartPtr<Payment> > Account::history() const {
    return _history;
}
SmartPtr<Payment> Account::lastPayment() const {
    vector<SmartPtr<Payment> >::const_iterator it;
    if(!_history.empty())
        it = _history.end();
    return *it;
}
void Account::addPayment(const Payment& pay) {
    Payment* p = const_cast<Payment*> (&pay);
    _history.push_back(SmartPtr<Payment>(p));
}