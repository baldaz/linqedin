#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "user.h"
#include "username.h"
#include "userinfo.h"

class UserInfo;

class Account {
protected:
    Username* usr;
    UserInfo* info;
public:
    void alterAccount();
    UserInfo* displayProfile() const;
};
#endif