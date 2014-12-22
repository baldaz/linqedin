#include "user.h"
#include "linqnet.h"
#include "linqdb.h"

using std::vector;

User::User() : _acc(new Account()), _net(new LinqNet()) {}
User::User(Account* ac, LinqNet* lq) : _acc(ac), _net(lq) {}
User::User(const User& usr) /*: _acc(usr._acc), _net(usr._net)*/ : _acc(usr._acc->clone()), _net(usr._net->clone()) {}
User::~User() { delete _acc; delete _net; }
User& User::operator=(const User& usr) {
    if(this != &usr) {
        delete _acc;
        delete _net;
        _acc = usr._acc;
        _net = usr._net;
    }
    return *this;
}
void User::addContact(User* usr) {
    _net->addUser(usr);
}
void User::removeContact(Username* usr) {
    _net->removeUser(usr);
}
Account* User::account() const {
    return _acc;
}
LinqNet* User::net() const {
    return _net;
}

User::searchFunctor::searchFunctor(int s = 0) : _s_type(s) {}
void User::searchFunctor::operator()(const SPUser& spu) const {
    switch(_s_type) {
        case 1:
            std::cout << "Basic search" << std::endl;
        break;
        case 2:
            std::cout << "Business search" << std::endl;
        break;
        case 3:
            std::cout << "Executive search" << std::endl;
        break;
        default:
            std::cout << "Schifo search" << std::endl;
        break;
    }
}

BasicUser::BasicUser() : User() {}
BasicUser::BasicUser(Account* ac, LinqNet* lq) : User(ac, lq) {}
BasicUser::BasicUser(const BasicUser& usr) : User(usr) {}
User* BasicUser::clone() const {
    return new BasicUser(*this);
}
void BasicUser::userSearch(const LinqDB& db) const {
    std::for_each(db.begin(), db.end(), searchFunctor(1));
}

BusinessUser::BusinessUser() : BasicUser() {}
BusinessUser::BusinessUser(Account* ac, LinqNet* lq) : BasicUser(ac, lq) {}
BusinessUser::BusinessUser(const BusinessUser& usr) : BasicUser(usr) {}
User* BusinessUser::clone() const {
    return new BusinessUser(*this);
}
void BusinessUser::userSearch(const LinqDB& db) const {
    std::for_each(db.begin(), db.end(), searchFunctor(2));
}

ExecutiveUser::ExecutiveUser() : BusinessUser() {}
ExecutiveUser::ExecutiveUser(Account* ac, LinqNet* lq) : BusinessUser(ac, lq) {}
ExecutiveUser::ExecutiveUser(const ExecutiveUser& usr) : BusinessUser(usr) {}
User* ExecutiveUser::clone() const {
    return new ExecutiveUser(*this);
}
void ExecutiveUser::userSearch(const LinqDB& db) const {
    std::for_each(db.begin(), db.end(), searchFunctor(3));
}