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
#include "error.h"

using std::map;
using std::list;

class LinqNet;
class LinqDB;
class Group;
class Post;

class User {
private:
    Account* _acc;
    LinqNet* _net;
    int _visitcount;
    list<SmartPtr<Message> > _outMail;
    list<SmartPtr<Message> > _inMail;
protected:
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
    void loadOutMail(const Message&);
    list<SmartPtr<Message> > inMail() const;
    list<SmartPtr<Message> > outMail() const;
    int outMailCount() const;
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
    virtual void sendMessage(const Message&) throw(Error);
    static unsigned int basicLimit();
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
    virtual void sendMessage(const Message&) throw(Error);
    list<Group*> groups() const;
    void addGroup(const Group&);
    void removeGroup(const Group&);
    // void addPost(const Group&, const Post&);
    void addBio(const string&) const;
    static unsigned int businessLimit();
};

class ExecutiveUser : public BusinessUser {
private:
    map<string, int> _keywords;
    list<SmartPtr<User> > _visitors;

    class RemoveGroup {
    private:
        Group* gr;
    public:
        RemoveGroup(Group*);
        void operator()(const SmartPtr<User>&);
    };
public:
    ExecutiveUser(Account*);
    ExecutiveUser(const ExecutiveUser&);
    ExecutiveUser& operator=(const ExecutiveUser&);
    virtual ~ExecutiveUser();
    virtual User* clone() const;
    virtual map<string, string> userSearch(const LinqDB&, const string&) const;
    virtual void sendMessage(const Message&) throw(Error);
    void globalRemoveGroup(const LinqDB&, const Group&);
    void addKeyword(const string&);
    map<string, int> keywordPercent() const;
    map<string, int> keywords() const;
    void addVisitor(const SmartPtr<User>&);
    list<SmartPtr<User> > visitors() const;
    static unsigned int executiveLimit();
};

#endif