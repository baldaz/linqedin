#ifndef LINQCLIENT_H
#define LINQCLIENT_H

#include "user.h"
#include "linqdb.h"
#include "utils.h"
#include <string>
#include <sstream>

using std::string;

const string STANDARD_AVATAR = "img/port2.jpg";

class LinqClient {
private:
    User* _usr;
    LinqDB* _db;
    string _avatar;
public:
    LinqClient();
    LinqClient(const Username&);
    ~LinqClient();
    int netSize() const;
    vector<SmartPtr<User> > similarity() const;
    bool linked(const Username&) const;
    void setAvatar(const string& = STANDARD_AVATAR);
    string avatar() const;
    string displayProfile() const;
    string displayHtmlInfo() const;
    string displayHtmlPayments() const;
    string displayHtmlSettings() const;
    string displayHtmlMessages() const;
    vector<string> skills() const;
    vector<string> interests() const;
    vector<string> languages() const;
    vector<string> displayHtmlNet() const;
    vector<SmartPtr<User> > contactsInfo() const;
    list<SmartPtr<Message> > inMail() const;
    list<SmartPtr<Message> > outMail() const;
    void alterProfile();
    void addContact(const Username&);
    void removeContact(const Username&);
    void addExperience(const Experience&);
    void addVisitTo(const Username&);
    void sendMail(const string& = "",  const string& = "", const string& = "", bool = false);
    map<string, string> find(const string&) const;
    map<string, int> keywordFrequency() const;
    int visitCount() const;
    void save() const;
};
#endif