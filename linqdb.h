#ifndef LINQDB_H
#define LINQDB_H

#include <iostream>
#include <vector>
#include <QFile>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QString>
#include <string>
#include "spuser.h"
#include "linqnet.h"
#include "privlevel.h"
#include "smartptr.h"

using std::ostream;
using std::vector;
using std::string;

class LinqDB {
private:
    vector<SmartPtr<User> > _db;
    bool fromJsonObject();
    void read(const QJsonArray&);
    void readNet(const QJsonArray&);
    vector<QJsonObject> toJsonObject() const;
    void write(vector<QJsonObject>) const;
public:
    LinqDB();
    ~LinqDB();
    void load();
    void save() const;
    void addUser(User*);
    void removeUser(Username*);
    int size() const;
    User* find(Username*);
    vector<SmartPtr<User> >::const_iterator begin() const;
    vector<SmartPtr<User> >::const_iterator end() const;
    SmartPtr<User> operator[](const int&) const;
    friend ostream& operator<<(ostream&, const LinqDB&);
};
#endif