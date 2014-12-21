#ifndef LINQDB_H
#define LINQDB_H

#include <iostream>
#include <algorithm>
#include <vector>
#include <QFile>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QString>
#include "spuser.h"
#include "linqnet.h"
#include "privlevel.h"

using std::ostream;
using std::vector;

class LinqDB {
private:
    vector<SPUser> _db;
    bool fromJsonObject();
    void read(const QJsonArray&);
    vector<QJsonObject> toJsonObject() const;
    void write(vector<QJsonObject>) const;
public:
    LinqDB();
    ~LinqDB();
    void load();
    void save() const;
    int size() const;
    void addUser(User*);
    void removeUser(User*);
    User* find(Username*);
    SPUser operator[](const int&) const;
    friend ostream& operator<<(ostream&, const LinqDB&);
};
#endif