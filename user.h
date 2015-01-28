#ifndef USER_H
#define USER_H


#include <vector>
#include <map>
#include <list>
#include <typeinfo>
#include <algorithm>
#include "account.h"
#include "smartptr.h"
#include "message.h"
#include "group.h"

using std::map;
using std::list;

class LinqNet;
class LinqDB;
class Group;

class User {
private:
    Account* _acc;
    LinqNet* _net;
    int _visitcount;
protected:
    list<SmartPtr<Message> > _outMail;
    list<SmartPtr<Message> > _inMail;
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
    User(Account*);
    User(const User&);
    User& operator=(const User&);
    virtual ~User();
    virtual User* clone() const =0;
    Account* account() const;
    LinqNet* net() const;
    void addContact(User*);
    void removeContact(const Username&);
    int visitCount() const;
    void setVisitCount(int);
    void addVisit();
    int similarity(const SmartPtr<User>&) const;
    bool linked(const Username&) const;
    vector<SmartPtr<User> > listPossibleLinks(const LinqDB&) const;
    virtual map<string, string> userSearch(const LinqDB&, const string&) const =0;
    virtual void sendMessage(const Message&) =0;
    void loadInMail(const Message&);
    virtual void loadOutMail(const Message&) =0;
    list<SmartPtr<Message> > inMail() const;
    list<SmartPtr<Message> > outMail() const;
    void setInMail(const list<SmartPtr<Message> >&);
};

class BasicUser : public User {
private:
    static unsigned int basicMailLimit;
public:
    BasicUser(Account*);
    BasicUser(const BasicUser&);
    BasicUser& operator=(const BasicUser&);
    virtual User* clone() const;
    virtual map<string, string> userSearch(const LinqDB&, const string&) const;
    virtual void sendMessage(const Message&);
    virtual void loadOutMail(const Message&);
};

class BusinessUser : public BasicUser {
private:
    list<Group*> _groups;
    static unsigned int businessMailLimit;
public:
    BusinessUser(Account*);
    BusinessUser(const BusinessUser&);
    BusinessUser& operator=(const BusinessUser&);
    virtual ~BusinessUser();
    virtual User* clone() const;
    virtual map<string, string> userSearch(const LinqDB&, const string&) const;
    virtual void sendMessage(const Message&);
    virtual void loadOutMail(const Message&);
    list<Group*> groups() const;
    void addGroup(const Group&);
    void addBio(const string&) const;
};

class ExecutiveUser : public BusinessUser {
protected:
    map<string, int> _keywords;
    list<SmartPtr<User> > _visitors;
public:
    ExecutiveUser(Account*);
    ExecutiveUser(const ExecutiveUser&);
    ExecutiveUser& operator=(const ExecutiveUser&);
    virtual ~ExecutiveUser();
    virtual User* clone() const;
    virtual map<string, string> userSearch(const LinqDB&, const string&) const;
    virtual void sendMessage(const Message&);
    virtual void loadOutMail(const Message&);
    void addKeyword(const string&);
    map<string, int> keywordPercent() const;
    map<string, int> keywords() const;
    void addVisitor(const SmartPtr<User>&);
    list<SmartPtr<User> > visitors() const;
};

#endif