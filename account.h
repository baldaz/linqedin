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
    Account();
    Account(Info*, Username*, privLevel);
    Account(const Account&);
    ~Account();
    Account* clone() const;
    Account& operator=(const Account&);
    Username* username() const;
    Info* info() const;
    privLevel prLevel() const;
    void setInfo(Info*);
};
#endif