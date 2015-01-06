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
    LinqClient(const Username&);
    ~LinqClient();
    int netSize() const;
    string displayProfile() const;
    string displayHtmlInfo() const;
    vector<string> displayHtmlNet() const;
    vector<SmartPtr<User> > contactsInfo() const;
    void alterProfile();
    void addContact(const Username&);
    void removeContact(const Username&);
    void addExperience(const Experience&);
    void addFormation(const Experience&);
    string find(string) const;
    void save() const;
};
#endif