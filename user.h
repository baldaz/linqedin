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
    virtual void sendMessage(const Username&, const string& = "", const string& = "", bool = false) =0;
    void loadInMail(const Message&);
    virtual void loadOutMail(const Message&) =0;
    list<Message*> inMail() const;
    list<Message*> outMail() const;
};

class BasicUser : public User {
private:
    static unsigned int basicMailLimit;
public:
    BasicUser(Account*);
    BasicUser(const BasicUser&);
    virtual User* clone() const;
    virtual map<string, string> userSearch(const LinqDB&, const string&) const;
    virtual void sendMessage(const Username&, const string& = "", const string& = "", bool = false);
    virtual void loadOutMail(const Message&);
};

class BusinessUser : public BasicUser {
private:
    static unsigned int businessMailLimit;
public:
    BusinessUser(Account*);
    BusinessUser(const BusinessUser&);
    virtual User* clone() const;
    virtual map<string, string> userSearch(const LinqDB&, const string&) const;
    virtual void sendMessage(const Username&, const string& = "", const string& = "", bool = false);
    virtual void loadOutMail(const Message&);
};

class ExecutiveUser : public BusinessUser {
protected:
    map<string, int> _keywords;
public:
    ExecutiveUser(Account*);
    ExecutiveUser(const ExecutiveUser&);
    virtual ~ExecutiveUser();
    virtual User* clone() const;
    virtual map<string, string> userSearch(const LinqDB&, const string&) const;
    virtual void sendMessage(const Username&, const string& = "", const string& = "", bool = false);
    virtual void loadOutMail(const Message&);
    virtual void addKeyword(const string&);
    virtual map<string, int> keywordPercent() const;
    virtual map<string, int> keywords() const;
};

#endif