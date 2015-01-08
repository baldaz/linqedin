#ifndef USER_H
#define USER_H

#include "account.h"
#include <vector>
#include <smartptr.h>

class LinqNet;
class LinqDB;

class User {
protected:
    Account* _acc;
    LinqNet* _net;
    int _visitcount;
    class searchFunctor {
    private:
        int _s_type;
        string _wanted;
        string _result;
    public:
        searchFunctor(int, string);
        void operator()(const SmartPtr<User>&);
        string result() const;
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
    int visitCount() const;
    void setVisitCount(int);
    void addVisit();
    int similarity(User*) const;
    virtual string userSearch(const LinqDB&, string) const =0;
};

class BasicUser : public User {
public:
    BasicUser();
    BasicUser(Account*, LinqNet*);
    BasicUser(const BasicUser&);
    virtual User* clone() const;
    virtual string userSearch(const LinqDB&, string) const;
};

class BusinessUser : public BasicUser {
protected:
    class linkedWith {
    private:
        int _links;
        User* _owner;
        vector<SmartPtr<User> > _mates;
    public:
        linkedWith(int, User*);
        void operator()(const SmartPtr<User>&);
        vector<SmartPtr<User> > result() const;
    };
public:
    BusinessUser();
    BusinessUser(Account*, LinqNet*);
    BusinessUser(const BusinessUser&);
    virtual User* clone() const;
    vector<SmartPtr<User> > listPossibleLinks(const LinqDB&) const;
    virtual string userSearch(const LinqDB&, string) const;
};

class ExecutiveUser : public BusinessUser {
public:
    ExecutiveUser();
    ExecutiveUser(Account*, LinqNet*);
    ExecutiveUser(const ExecutiveUser&);
    virtual User* clone() const;
    virtual string userSearch(const LinqDB&, string) const;
};

#endif