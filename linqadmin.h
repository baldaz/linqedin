#ifndef LINQADMIN_H
#define LINQADMIN_H

#include "username.h"
#include "linqdb.h"
#include "error.h"

class LinqAdmin {
private:
    class completeRemove {
    private:
        Username rmusr;
        Group* g;
        int mode;
    public:
        completeRemove(const Username&, int = 0);
        completeRemove(Group*, int = 1);
        ~completeRemove();
        void operator()(const SmartPtr<User>&) const;
    };
    class adminSearch {
        string _wanted;
        map<string,string> _result;
    public:
        adminSearch(const string&);
        void operator()(const SmartPtr<User>&);
        map<string,string> result() const;
    };
    LinqDB* _db;
public:
    LinqAdmin();
    ~LinqAdmin();
    list<SmartPtr<User> > listUsers() const;
    void insertUser(User*);
    void insertUser(const string&, const string&, privLevel, const map<string, string>& = map<string,string>()) throw(Error);
    void removeUser(const Username&);
    map<string,string> find(const string&) const;
    Group findGroup(const string&) const;
    list<Group*> listGroups() const;
    list<Group*> listUserGroups(const Username&) const;
    list<Post*> listPostFromGroup(const Group&) const;
    void deleteGroup(const string&);
    void upgradeSubscription(const Username&, privLevel);
    void save() const;
};
#endif