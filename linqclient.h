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
    int level() const;
    int netSize() const;
    vector<SmartPtr<User> > similarity() const;
    bool linked(const Username&) const;
    void setAvatar(const string& = STANDARD_AVATAR);
    Username username() const;
    string avatar() const;
    string displayProfile() const;
    string displayHtmlInfo() const;
    string displayHtmlPayments() const;
    string displayHtmlSettings() const;
    string displayHtmlMessages() const;
    string avatarFromUser(const Username&) const;
    vector<string> skills() const;
    vector<string> interests() const;
    vector<string> languages() const;
    vector<string> displayHtmlNet() const;
    vector<SmartPtr<User> > contactsInfo() const;
    list<SmartPtr<User> > visitors() const;
    list<SmartPtr<Message> > inMail() const;
    list<SmartPtr<Message> > outMail() const;
    list<Group*> listGroups() const;
    list<Group*> listAllGroups() const;
    list<Post*> listPostFromGroup(const Group&) const;
    int postNumberFromGroup(const Group&) const;
    void alterProfile(const map<int, string>&);
    void addContact(const Username&);
    void removeContact(const Username&);
    void addExperience(const Experience&);
    void addVisitTo(const Username&);
    void sendMail(const string& = "",  const string& = "", const string& = "", bool = false);
    void modifyInMail(const list<SmartPtr<Message> >&);
    void addPostToGroup(const Group&, const Post&);
    void createNewGroup(const Group&);
    void addGroup(const Group&);
    void addGroup(const string&, const string&);
    void deleteGroup(const string&, const string&);
    Group findGroup(const string&) const;
    map<string, string> find(const string&) const;
    map<string, int> keywordFrequency() const;
    int visitCount() const;
    void save() const;
};
#endif