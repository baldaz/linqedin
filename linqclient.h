#ifndef LINQCLIENT_H
#define LINQCLIENT_H

#include "user.h"
#include "linqdb.h"
#include "utils.h"
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
    vector<SmartPtr<User> > similarity() const;
    bool linked(const Username&) const;
    string displayProfile() const;
    string displayHtmlInfo() const;
    string displayHtmlPayments() const;
    string displayHtmlSettings() const;
    string displayHtmlMessages() const;
    vector<string> displayHtmlNet() const;
    vector<SmartPtr<User> > contactsInfo() const;
    void alterProfile();
    void addContact(const Username&);
    void removeContact(const Username&);
    void addExperience(const Experience&);
    void addFormation(const Experience&);
    void addVisitTo(const Username&);
    map<string, string> find(const string&) const;
    void save() const;
};
#endif