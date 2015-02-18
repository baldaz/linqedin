#ifndef GROUP_H
#define GROUP_H

#include "user.h"
#include "post.h"

class User;

class Group {
private:
    Username _admin;
    list<Post*> _posts;
    list<SmartPtr<User> > _members;
    string _name;
    string _description;
public:
    Group(const Username& u, const string& n = "", const string& d = "");
    Group(const Group&);
    ~Group();
    bool operator==(const Group&) const;
    bool isMember(const Username&) const;
    int postNumber() const;
    Username admin() const;
    string name() const;
    string description() const;
    list<SmartPtr<User> > members() const;
    list<Post*> posts() const;
    void addMember(User*);
    void removeMember(const Username&) throw(Error);
    void insertPost(const Post&);
    void clearPosts();
};
#endif
