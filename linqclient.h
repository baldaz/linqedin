#ifndef LINQCLIENT_H
#define LINQCLIENT_H

#include "user.h"
#include "linqdb.h"
#include <string>

using std::string;

class LinqClient {
private:
    User* _usr;
    LinqDB* _db;
public:
    LinqClient();
    LinqClient(Username*);
    ~LinqClient();
    string displayProfile() const;
    string displayHtmlInfo() const;
    string displayHtmlNet() const;
    void alterProfile();
    void addContact(Username*);
    void removeContact(Username*);
    void addExperience(Experience*);
    void addFormation(Experience*);
    string find() const;
    void save() const;
};
#endif