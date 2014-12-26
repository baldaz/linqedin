#ifndef LINQCLIENT_H
#define LINQCLIENT_H

#include "user.h"
#include "linqdb.h"
#include <string>
#include <sstream>

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
    void alterProfile();
    void addContact(Username*);
    void removeContact(Username*);
    void addExperience(Experience*);
    void addFormation(Experience*);
    void find() const;
    void save() const;
};
#endif