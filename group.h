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
    User* _admin;
    list<SmartPtr<User> > _members;
    list<Post*> _posts;
    string _name, _description;
public:
    Group(User*, const string& = "", const string& ="");
    ~Group();
    User* admin() const;
    string name() const;
    string description() const;
    list<SmartPtr<User> > members() const;
    void addMember(User*);
    void insertPost(const Post&);
    string print() const;
};
#endif