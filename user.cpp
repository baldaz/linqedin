#include "user.h"

User::User() : references(0) {}
User::User(Account* ac, LinqNet* lq) : _acc(ac), _net(lq), references(0) {}
User::User(const User& usr) : _acc(usr._acc), _net(usr._net), references(0) {}
User::~User() {}
Username* User::getUsername() const {
    return _acc->getUsername();
}

BasicUser::BasicUser() : User() {}
BasicUser::BasicUser(Account* ac, LinqNet* lq) : User(ac, lq) {}
BasicUser::BasicUser(const BasicUser& usr) : User(usr) {}
void BasicUser::userSearch(const LinqDB& db) const {}

BusinessUser::BusinessUser() : BasicUser() {}
BusinessUser::BusinessUser(Account* ac, LinqNet* lq) : BasicUser(ac, lq) {}
BusinessUser::BusinessUser(const BusinessUser& usr) : BasicUser(usr) {}
void BusinessUser::userSearch(const LinqDB& db) const {}

ExecutiveUser::ExecutiveUser() : BusinessUser() {}
ExecutiveUser::ExecutiveUser(Account* ac, LinqNet* lq) : BusinessUser(ac, lq) {}
ExecutiveUser::ExecutiveUser(const ExecutiveUser& usr) : BusinessUser(usr) {}
void ExecutiveUser::userSearch(const LinqDB& db) const {}