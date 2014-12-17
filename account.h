#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "username.h"
#include "info.h"

// class UserInfo;

class Account {
private:
    Info* _info;
    Username* _user;
public:
    Account(Info*, Username*);
    Username* getUsername() const;
    Info* getInfo() const;
    void setInfo(Info*);
};
#endif