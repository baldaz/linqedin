#ifndef LINQDB_H
#define LINQDB_H

#include <vector>
#include "user.h"

class User;

class LinqDB {
private:
    class SPUser {
    public:
        User* usr;
        SPUser(User*);
        SPUser(const SPUser&);
        ~SPUser();
        SPUser& operator=(const SPUser&);
        User& operator*() const;
        User* operator->() const;
        bool operator==(const SPUser&) const;
        bool operator!=(const SPUser&) const;
    };
public:
    vector<SPUser> db;
    void load();
    void save() const;
    User* find(Username);
};
#endif