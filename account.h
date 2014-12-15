#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "username.h"
#include "userinfo.h"

// class UserInfo;

class Account {
private:
    UserInfo* _info;
    Username* _user;
public:
    Account(UserInfo*, Username*);
    Username* getUsername() const;
    UserInfo* getInfo() const;
    void setInfo(UserInfo*);
};
#endif