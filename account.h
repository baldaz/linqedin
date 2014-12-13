#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "user.h"
#include "username.h"
#include "userinfo.h"

class UserInfo;

class Account {
private:
    UserInfo* info;
protected:
    Username* user;
public:
    UserInfo* getInfo() const;
    void setInfo(const UserInfo&);
};
#endif