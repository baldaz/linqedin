#include "user.h"
#include "linqnet.h"

using std::vector;

User::User() {}
User::User(Account* ac, LinqNet* lq) : _acc(ac), _net(lq) {}
User::User(const User& usr) : _acc(usr._acc), _net(usr._net) {}
User::~User() { delete _acc; delete _net; }
Account* User::account() const {
    return _acc;
}
LinqNet* User::net() const {
    return _net;
}

BasicUser::BasicUser() : User() {}
BasicUser::BasicUser(Account* ac, LinqNet* lq) : User(ac, lq) {}
BasicUser::BasicUser(const BasicUser& usr) : User(usr) {}
User* BasicUser::clone() const {
    return new BasicUser(*this);
}
void BasicUser::userSearch(const LinqDB& db) const {}

BusinessUser::BusinessUser() : BasicUser() {}
BusinessUser::BusinessUser(Account* ac, LinqNet* lq) : BasicUser(ac, lq) {}
BusinessUser::BusinessUser(const BusinessUser& usr) : BasicUser(usr) {}
User* BusinessUser::clone() const {
    return new BusinessUser(*this);
}
void BusinessUser::userSearch(const LinqDB& db) const {}

ExecutiveUser::ExecutiveUser() : BusinessUser() {}
ExecutiveUser::ExecutiveUser(Account* ac, LinqNet* lq) : BusinessUser(ac, lq) {}
ExecutiveUser::ExecutiveUser(const ExecutiveUser& usr) : BusinessUser(usr) {}
User* ExecutiveUser::clone() const {
    return new ExecutiveUser(*this);
}
void ExecutiveUser::userSearch(const LinqDB& db) const {}