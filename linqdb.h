#ifndef LINQDB_H
#define LINQDB_H

#include <vector>
#include "user.h"

using std::vector;

class User;

class LinqDB {
private:
    void writeXML(); /*scrivere su XML*/
public:
    class SPUser {
    public:
        User* _p_usr;
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
    void load();
    void save() const;
    void addUser(const SPUser&);
    void removeUser(const SPUser&);
    User* find(Username);
};
#endif