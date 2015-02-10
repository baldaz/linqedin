#ifndef GROUP_H
#define GROUP_H

#include <string>
#include <list>
#include "user.h"
#include "post.h"

class User;

using std::string;
using std::list;

class Group {
private:
    Username _admin;
    list<Post*> _posts;
    list<SmartPtr<User> > _members;
    string _name;
    string _description;
public:
    // Group();
    Group(const Username& u, const string& n = "", const string& d = "");
    Group(const Group&);
    ~Group();
    bool operator==(const Group&) const;
    int postNumber() const;
    Username admin() const;
    string name() const;
    string description() const;
    list<SmartPtr<User> > members() const;
    list<Post*> posts() const;
    void addMember(User*);
    void insertPost(const Post&);
    string print() const;
};
#endif
