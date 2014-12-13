#ifndef USER_H
#define USER_H

#include "account.h"
#include "username.h"

class LinQNet;

class User {
public:
    Account* acc;
    LinQNet* net;
    Username usr;
    User(Username);
    virtual ~User();
};

class Basic : public User {};

class Business : public Basic {};

class Executive : public Business {};

#endif