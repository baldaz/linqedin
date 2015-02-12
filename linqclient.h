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
    int userSimilarity(const SmartPtr<User>&) const;
    vector<SmartPtr<User> > similarity() const;
    bool linked(const Username&) const;
    void setAvatar(const string& = STANDARD_AVATAR);
    Username username() const;
    Info* info() const;
    string avatar() const;
    string displayProfile() const;
    string displayHtmlInfo() const;
    string avatarFromUser(const Username&) const;
    vector<string> skills() const;
    vector<string> interests() const;
    vector<string> languages() const;
    list<Experience*> experiences() const;
    vector<string> displayHtmlNet() const;
    vector<SmartPtr<User> > contactsInfo() const;
    vector<SmartPtr<Payment> > paymentHistory() const;
    list<SmartPtr<User> > visitors() const;
    list<SmartPtr<Message> > inMail() const;
    list<SmartPtr<Message> > outMail() const;
    list<Group*> listGroups() const;
    list<Group*> listAllGroups() const;
    list<Group*> listUserGroups(const Username&) const;
    list<Post*> listPostFromGroup(const Group&) const;
    int postNumberFromGroup(const Group&) const;
    void alterProfile(int, const string&) throw(Error);
    void requestUpgrade(const string&, const string&, privLevel) throw(Error);
    void removeExperience(const Experience&);
    void addContact(const Username&);
    void removeContact(const Username&);
    void addExperience(const Experience&);
    void addVisitTo(const Username&);
    void sendMail(const string& = "",  const string& = "", const string& = "", bool = false);
    void modifyInMail(const list<SmartPtr<Message> >&);
    void addPostToGroup(const Group&, const Post&);
    void createNewGroup(const Group&) throw(Error);
    void addGroup(const Group&);
    void addGroup(const string&, const string&);
    void deleteGroup(const string&, const string&);
    void addTrait(int, const string&);
    void deleteTrait(int, const string&);
    void deleteMessage(const Message&);
    Group findGroup(const string&) const;
    map<string, string> find(const string&) const;
    map<string, int> keywordFrequency() const;
    int visitCount() const;
    int outMailCount() const;
    int outMailLimit() const;
    void save() const;
};
#endif