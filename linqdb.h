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

using std::ostream;
using std::vector;
using std::string;

class LinqDB {
private:
    vector<SPUser> _db;
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
    vector<SPUser>::const_iterator begin() const;
    vector<SPUser>::const_iterator end() const;
    SPUser operator[](const int&) const;
    friend ostream& operator<<(ostream&, const LinqDB&);
};
#endif