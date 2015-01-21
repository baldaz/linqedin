#ifndef LINQNET_H
#define LINQNET_H

#include <iostream>
#include <vector>
#include <list>
#include "user.h"

using std::list;
using std::vector;
using std::ostream;

class LinqNet {
private:
    list<SmartPtr<User> > _net;
public:
    LinqNet();
    LinqNet(const LinqNet&);
    ~LinqNet();
    LinqNet* clone() const;
    void addUser(User*);
    void removeUser(const Username&);
    int size() const;
    vector<Username> username() const;
    // SmartPtr<User> operator[](const int&) const;
    string printHtml() const;
    list<SmartPtr<User> >::const_iterator begin() const;
    list<SmartPtr<User> >::const_iterator end() const;
    friend ostream& operator<<(ostream&, const LinqNet&);
};
#endif