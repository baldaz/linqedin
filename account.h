#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "username.h"
#include "userinfo.h"

// class UserInfo;

class Account {
private:
    UserInfo* _info;
protected:
    Username* _user;
public:
    Account(UserInfo*, Username*);
    UserInfo* getInfo() const;
    void setInfo(UserInfo*);
};
#endif