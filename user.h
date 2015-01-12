#ifndef USER_H
#define USER_H


#include <vector>
#include <algorithm>
#include "account.h"
#include "smartptr.h"

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
        const User* _caller;
        vector<string> _result;
    public:
        searchFunctor(int, const string&, const User*);
        void operator()(const SmartPtr<User>&);
        vector<string> result() const;
    };
public:
    User();
    User(Account*, LinqNet*);
    User(const User&);
    User& operator=(const User&);
    virtual ~User();
    virtual User* clone() const =0;
    virtual Account* account() const =0;
    virtual LinqNet* net() const =0;
    virtual void addContact(User*) =0;
    virtual void removeContact(const Username&) =0;
    virtual int visitCount() const =0;
    virtual void setVisitCount(int) =0;
    virtual void addVisit() =0;
    virtual int similarity(User*) const =0;
    virtual bool linked(const Username&) const =0;
    virtual vector<SmartPtr<User> > listPossibleLinks(const LinqDB&) const =0;
    virtual vector<string> userSearch(const LinqDB&, const string&) const =0;
};

class BasicUser : public User {
protected:
    class linkedWith {
    private:
        int _offset;
        User* _owner;
        vector<SmartPtr<User> > _mates;
    public:
        linkedWith(int, User*);
        void operator()(const SmartPtr<User>&);
        vector<SmartPtr<User> > result() const;
    };
public:
    BasicUser();
    BasicUser(Account*, LinqNet*);
    BasicUser(const BasicUser&);
    virtual User* clone() const;
    virtual Account* account() const;
    virtual LinqNet* net() const;
    virtual void addContact(User*);
    virtual void removeContact(const Username&);
    virtual int visitCount() const;
    virtual void setVisitCount(int);
    virtual void addVisit();
    virtual int similarity(User*) const;
    virtual bool linked(const Username&) const;
    virtual vector<SmartPtr<User> > listPossibleLinks(const LinqDB&) const;
    virtual vector<string> userSearch(const LinqDB&, const string&) const;
};

class BusinessUser : public BasicUser {
public:
    BusinessUser();
    BusinessUser(Account*, LinqNet*);
    BusinessUser(const BusinessUser&);
    virtual User* clone() const;
    virtual vector<string> userSearch(const LinqDB&, const string&) const;
};

class ExecutiveUser : public BusinessUser {
public:
    ExecutiveUser();
    ExecutiveUser(Account*, LinqNet*);
    ExecutiveUser(const ExecutiveUser&);
    virtual User* clone() const;
    virtual vector<string> userSearch(const LinqDB&, const string&) const;
};

#endif