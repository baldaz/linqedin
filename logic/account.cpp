#include "account.h"

Account::Account(Info* uf, const Username& us, privLevel l = basic) : _info(uf->clone()), _user(us), _privilege(l) {}
Account::Account(const Account& acc) : _info(acc._info->clone()), _user(acc._user), _privilege(acc._privilege), _history(acc._history), _avatar(acc._avatar) {}
Account::~Account() {delete _info; _history.clear();}
Account* Account::clone() const {
    return new Account(*this);
}
Account& Account::operator=(const Account& acc) {
    if(this != &acc) {
        delete _info;
        _info = acc._info->clone();
        _user = acc._user;
        _privilege = acc._privilege;
        _history = acc._history;
    }
    return *this;
}
const Username& Account::username() const {
    return _user;
}
Username& Account::username() {
    return _user;
}
Info* Account::info() const {
    return _info;
}
privLevel Account::prLevel() const {
    return _privilege;
}
Avatar Account::avatar() const {
    return _avatar;
}
void Account::setAvatar(const Avatar& a){
    _avatar = a;
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
const SmartPtr<Payment>& Account::lastPayment() const throw(Error) {
    if(!_history.empty())
        return _history.back();
    else throw Error(payment, "No payment added yet");
}
void Account::addPayment(const Payment& pay) {
    Payment* p = const_cast<Payment*> (&pay);
    _history.push_back(SmartPtr<Payment>(p));
}
