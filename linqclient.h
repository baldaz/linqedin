#ifndef LINQCLIENT_H
#define LINQCLIENT_H

#include "user.h"
#include "linqdb.h"

class LinqClient {
private:
    User* _usr;
    LinqDB* _db;
public:
    LinqClient();
    LinqClient(Username*);
    ~LinqClient();
    void displayProfile() const;
    void alterProfile();
    void addContact(Username*);
    void removeContact(Username*);
    void addExperience(Experience*);
    void addFormation(Experience*);
    void find() const;
    void save() const;
};
#endif