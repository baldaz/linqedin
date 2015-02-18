#ifndef LINQNET_H
#define LINQNET_H

// #include <vector>
// #include <list>
#include "user.h"
// #include "error.h"

// using std::list;
// using std::vector;

class LinqNet {
private:
    list<SmartPtr<User> > _net;
public:
    LinqNet();
    LinqNet(const LinqNet&);
    ~LinqNet();
    LinqNet* clone() const;
    void addUser(User*) throw(Error);
    void removeUser(const Username&) throw(Error);
    int size() const;
    vector<Username> username() const;
    string printHtml() const;
    list<SmartPtr<User> >::const_iterator begin() const;
    list<SmartPtr<User> >::const_iterator end() const;
};
#endif