#ifndef USER_H
#define USER_H

#include "account.h"
#include "username.h"
#include "linqdb.h"

class LinqNet;
class LinqDB;

class User {
protected:
    Account* _acc;
    LinqNet* _net;
public:
    int references;
    User();
    User(Account*, LinqNet*);
    User(const User&);
    virtual ~User();
    Username* getUsername() const;
    virtual void userSearch(const LinqDB&) const =0;
};

class BasicUser : public User {
public:
    BasicUser();
    BasicUser(Account*, LinqNet*);
    BasicUser(const BasicUser&);
    virtual void userSearch(const LinqDB&) const;
};

class BusinessUser : public BasicUser {};

class ExecutiveUser : public BusinessUser {};

#endif