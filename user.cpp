#include "user.h"

User::User() : references(0) {}
User::User(Account* ac, LinqNet* lq) : _acc(ac), _net(lq), references(0) {}
User::User(const User& usr) : _acc(usr._acc), _net(usr._net), references(0) {}
User::~User() {}
Username* User::getUsername() const {
    return _acc->getUsername();
}