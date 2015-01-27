#include "group.h"

Group::Group(User* u, const string& n, const string& d) : _admin(u->clone()), _name(n), _description(d) {}
Group::~Group() {
    for(list<Post*>::iterator i = _posts.begin(); i != _posts.end(); ++i)
        delete *i;
    _posts.clear();
    _members.clear();
}
User* Group::admin() const {
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
void Group::addMember(User* u) {
    _members.push_back(SmartPtr<User> (u));
}
void Group::insertPost(const Post& p) {
    _posts.push_back(const_cast<Post*> (&p));
}
string Group::print() const {
    return "";
}