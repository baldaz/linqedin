#ifndef LINQADMIN_H
#define LINQADMIN_H

#include "username.h"
#include "linqdb.h"

class LinqAdmin {
private:
    LinqDB* _db;
public:
    LinqAdmin();
    ~LinqAdmin();
    void insertUser(User*);
    void removeUser(Username*);
    void find() const;
    void alterSubscription(Username*, privLevel);
    void save() const;
};
#endif