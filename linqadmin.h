#ifndef LINQADMIN_H
#define LINQADMIN_H

#include "username.h"
#include "linqdb.h"

class LinqAdmin {
private:
    class completeRemove {
        Username rmusr;
    public:
        completeRemove(const Username&);
        ~completeRemove();
        void operator()(const SmartPtr<User>&) const;
    };
    LinqDB* _db;
public:
    LinqAdmin();
    ~LinqAdmin();
    list<SmartPtr<User> > listUsers() const;
    void insertUser(User*);
    void insertUser(const string&, const string&, const map<string, string>& = map<string,string>());
    void removeUser(const Username&);
    void find() const;
    void alterSubscription(const Username&, privLevel);
    void save() const;
};
#endif