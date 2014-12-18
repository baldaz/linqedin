#ifndef LINQDB_H
#define LINQDB_H

#include <iostream>
#include <vector>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QString>
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
    vector<SPUser> _db;
    void read(const QJsonObject&);
    void write(vector<QJsonObject>) const;
    vector<QJsonObject> toJson() const;
public:
    void load();
    void save() const;
    int size() const;
    void addUser(User*);
    void removeUser(User*);
    User* find(Username);
    SPUser operator[](const int&) const;
    friend ostream& operator<<(ostream&, const LinqDB&);
};
#endif