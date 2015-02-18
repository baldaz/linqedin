#ifndef USER_H
#define USER_H

#include "baseuser.h"
#include "group.h"

class Group;
class Post;

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
    void addGroup(const Group&) throw(Error);
    void removeGroup(const Group&);
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