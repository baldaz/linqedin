#ifndef LINQDB_H
#define LINQDB_H

#include <iostream>
#include <vector>
#include "user.h"

using std::ostream;
using std::vector;
// using std::set;

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
    vector<SPUser> _db;
    void writeXML(); /*scrivere su XML*/
public:
    void load();
    void save() const;
    int getSize() const;
    void addUser(User*);
    void removeUser(User*);
    User* find(Username);
    SPUser operator[](const int&) const;
    friend ostream& operator<<(ostream&, const LinqDB&);
};
#endif