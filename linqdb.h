#ifndef LINQDB_H
#define LINQDB_H

#include <iostream>
#include <vector>
#include "user.h"

using std::ostream;
using std::vector;

class User;

class LinqDB {
private:
    class SPUser {
    private:
        User* _p_usr;
    public:
        SPUser(User*);
        SPUser(const SPUser&);
        ~SPUser();
        SPUser& operator=(const SPUser&);
        User& operator*() const;
        User* operator->() const;
        bool operator==(const SPUser&) const;
        bool operator!=(const SPUser&) const;
    };
    void writeXML(); /*scrivere su XML*/
public:
    vector<SPUser> _db;
    void load();
    void save() const;
    void addUser(const User&);
    void removeUser(const SPUser&);
    User* find(Username);
    friend ostream& operator<<(ostream&, const LinqDB&);
};
#endif