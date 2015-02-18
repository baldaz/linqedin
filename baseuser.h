#ifndef BASEUSER_H
#define BASEUSER_H

#include <map>
#include <list>
// #include <vector>
#include "smartptr.h"
#include "message.h"
// #include "error.h"
#include "account.h"

using std::map;
using std::list;
using std::vector;

class LinqNet;
class LinqDB;

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
    string showInfo() const;
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
    void deleteMessage(const Message&) throw(Error);
    void loadInMail(const Message&);
    void loadOutMail(const Message&);
    list<SmartPtr<Message> > inMail() const;
    list<SmartPtr<Message> > outMail() const;
    int outMailCount() const;
    void setInMail(const list<SmartPtr<Message> >&);
};
#endif
