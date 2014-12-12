#ifndef USER_H
#define USER_H

#include "account.h"
#include "username.h"

class Network;

class User {
public:
    Account* acc;
    Network* net;
    Username usr;
    User(Username);
    virtual ~User();
};

#endif