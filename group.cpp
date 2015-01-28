#include "group.h"

Group::Group(const Username& u, const string& n, const string& d) : _admin(u), _name(n), _description(d) {}
Group::Group(const Group& g) : _admin(g._admin), _name(g._name), _description(g._description),/* _posts(g._posts),*/ _members(g._members) {
    for(list<Post*>::const_iterator i = g._posts.begin(); i != g._posts.end(); ++i)
        _posts.push_back(new Post(**i));
}
Group::~Group() {
    if(!_posts.empty()) {
        for(list<Post*>::iterator i = _posts.begin(); i != _posts.end(); ++i)
            delete *i;
        _posts.clear();
    }
    _members.clear();
}
Username Group::admin() const {
    return _admin;
}
string Group::name() const {
    return _name;
}
string Group::description() const {
    return _description;
}
list<SmartPtr<User> > Group::members() const {
    return _members;
}
list<Post*> Group::posts() const {
    return _posts;
}
void Group::addMember(User* u) {
    _members.push_back(SmartPtr<User> (u));
}
void Group::insertPost(const Post& p) {
    _posts.push_back(const_cast<Post*> (&p));
}
string Group::print() const {
    return "";
}