#ifndef LINQADMIN_H
#define LINQADMIN_H

#include "username.h"
#include "linqdb.h"

class LinqAdmin {
private:
    class completeRemove {
        Username* rmusr;
    public:
        completeRemove(Username*);
        ~completeRemove();
        void operator()(const SmartPtr<User>&) const;
    };
    LinqDB* _db;
public:
    LinqAdmin();
    ~LinqAdmin();
    void insertUser(User*);
    void removeUser(const Username&);
    void find() const;
    void alterSubscription(const Username&, privLevel);
    void save() const;
};
#endif