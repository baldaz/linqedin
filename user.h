#ifndef USER_H
#define USER_H

#include "account.h"
#include "username.h"
#include "linqdb.h"

class LinqNet;

class User {
protected:
    Account* _acc;
    LinqNet* _net;
public:
    int references;
    User();
    User(Account*, LinqNet*);
    User(const User&);
    Username* getUsername() const;
    virtual ~User();
};

class Basic : public User {};

class Business : public Basic {};

class Executive : public Business {};

#endif