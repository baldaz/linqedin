#ifndef USER_H
#define USER_H

#include "account.h"
#include "username.h"

class LinQNet;

class User {
protected:
    Account* _acc;
    LinQNet* _net;
public:
    int references;
    User(Account*, LinQNet*);
    virtual ~User();
};

class Basic : public User {};

class Business : public Basic {};

class Executive : public Business {};

#endif