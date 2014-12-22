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
    void insertUser();
    void removeUser();
    void find() const;
    void alterSubscription(Username*);
    void save() const;
};
#endif