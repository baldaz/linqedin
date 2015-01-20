#ifndef USER_H
#define USER_H


#include <vector>
#include <map>
#include <list>
#include <algorithm>
#include "account.h"
#include "smartptr.h"
#include "message.h"

using std::map;
using std::list;

class LinqNet;
class LinqDB;

class User {
protected:
    Account* _acc;
    LinqNet* _net;
    list<Message*> _outMail;
    list<Message*> _inMail;
    int _visitcount;
    class searchFunctor {
    private:
        int _s_type;
        string _wanted;
        const User* _caller;
        map<string, string> _result;
    public:
        searchFunctor(int, const string&, const User*);
        void operator()(const SmartPtr<User>&);
        map<string, string> result() const;
    };
public:
    // User();
    User(Account*);
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
    virtual map<string, string> userSearch(const LinqDB&, const string&) const =0;
    virtual void sendMessage(const Username&, const string& = "", const string& = "", bool = false) =0;
    virtual list<Message*> inMail() const =0;
    virtual list<Message*> outMail() const =0;
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
    // BasicUser();
    BasicUser(Account*);
    BasicUser(const BasicUser&);
    virtual ~BasicUser();
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
    virtual map<string, string> userSearch(const LinqDB&, const string&) const;
    virtual void sendMessage(const Username&, const string& = "", const string& = "", bool = false);
    virtual list<Message*> inMail() const;
    virtual list<Message*> outMail() const;
};

class BusinessUser : public BasicUser {
public:
    // BusinessUser();
    BusinessUser(Account*);
    BusinessUser(const BusinessUser&);
    virtual ~BusinessUser();
    virtual User* clone() const;
    virtual map<string, string> userSearch(const LinqDB&, const string&) const;
};

class ExecutiveUser : public BusinessUser {
protected:
    map<string, int> _keywords;
public:
    // ExecutiveUser();
    ExecutiveUser(Account*);
    ExecutiveUser(const ExecutiveUser&);
    virtual ~ExecutiveUser();
    virtual User* clone() const;
    virtual map<string, string> userSearch(const LinqDB&, const string&) const;
    virtual void addKeyword(const string&);
    virtual map<string, int> keywordPercent() const;
    virtual map<string, int> keywords() const;
};

#endif