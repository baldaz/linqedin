#ifndef USER_H
#define USER_H

#include "account.h"
#include <vector>
#include <smartptr.h>

class LinqNet;
class LinqDB;
// class SPUser;

class User {
protected:
    Account* _acc;
    LinqNet* _net;
    class searchFunctor {
    private:
        int _s_type;
    public:
        searchFunctor(int);
        void operator()(const SmartPtr<User>&) const;
    };
public:
    User();
    User(Account*, LinqNet*);
    User(const User&);
    User& operator=(const User&);
    virtual ~User();
    virtual User* clone() const =0;
    Account* account() const;
    LinqNet* net() const;
    void addContact(User*);
    void removeContact(Username*);
    virtual void userSearch(const LinqDB&) const =0;
};

class BasicUser : public User {
public:
    BasicUser();
    BasicUser(Account*, LinqNet*);
    BasicUser(const BasicUser&);
    virtual User* clone() const;
    virtual void userSearch(const LinqDB&) const;
};

class BusinessUser : public BasicUser {
public:
    BusinessUser();
    BusinessUser(Account*, LinqNet*);
    BusinessUser(const BusinessUser&);
    virtual User* clone() const;
    virtual void userSearch(const LinqDB&) const;
};

class ExecutiveUser : public BusinessUser {
public:
    ExecutiveUser();
    ExecutiveUser(Account*, LinqNet*);
    ExecutiveUser(const ExecutiveUser&);
    virtual User* clone() const;
    virtual void userSearch(const LinqDB&) const;
};

#endif