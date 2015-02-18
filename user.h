#ifndef USER_H
#define USER_H

#include "baseuser.h"
#include "group.h"

class Group;
class Post;

class BasicUser : public User {
private:
    static int basicMailLimit;
public:
    BasicUser(Account*);
    BasicUser(const BasicUser&);
    BasicUser& operator=(const BasicUser&);
    virtual User* clone() const;
    virtual map<string, string> userSearch(const LinqDB&, const string&) const;
    virtual void sendMessage(const Message&) throw(Error);
    static int basicLimit();
};

class BusinessUser : public BasicUser {
private:
    list<Group*> _groups;
    static int businessMailLimit;
    class linkedWith {
    private:
        int _offset;
        BusinessUser* _owner;
        vector<SmartPtr<User> > _mates;
    public:
        linkedWith(int, BusinessUser*);
        void operator()(const SmartPtr<User>&);
        vector<SmartPtr<User> > result() const;
    };
public:
    BusinessUser(Account*);
    BusinessUser(const BusinessUser&);
    BusinessUser& operator=(const BusinessUser&);
    virtual ~BusinessUser();
    virtual User* clone() const;
    virtual map<string, string> userSearch(const LinqDB&, const string&) const;
    virtual void sendMessage(const Message&) throw(Error);
    int similarity(const SmartPtr<User>&) const;
    vector<SmartPtr<User> > listPossibleLinks(const LinqDB&) const;
    list<Group*> groups() const;
    void addGroup(const Group&) throw(Error);
    void removeGroup(const Group&);    
    static int businessLimit();
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
    bool removeVisitorOccurences(const SmartPtr<User>&);
    list<SmartPtr<User> > visitors() const;
    static int executiveLimit();
};

#endif