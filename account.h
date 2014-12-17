#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "username.h"
#include "info.h"
#include "privlevel.h"

// class UserInfo;

class Account {
private:
    Info* _info;
    Username* _user;
    privLevel _privilege;
public:
    Account(Info*, Username*, privLevel);
    Username* getUsername() const;
    Info* getInfo() const;
    void setInfo(Info*);
};
#endif