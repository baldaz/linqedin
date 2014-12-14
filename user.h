#ifndef USER_H
#define USER_H

#include "account.h"
#include "username.h"

class LinQNet;

class User {
public:
    Account* _acc;
    LinQNet* _net;
    Username _usr;
    int references;
    User(Username);
    virtual ~User();
};

class Basic : public User {};

class Business : public Basic {};

class Executive : public Business {};

#endif