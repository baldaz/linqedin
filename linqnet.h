#ifndef LINQNET_H
#define LINQNET_H

#include <iostream>
#include <vector>
// #include "spuser.h"
#include "user.h"
#include "smartptr.h"

using std::vector;
using std::ostream;

class LinqNet {
private:
    vector<SmartPtr<User> > _net;
public:
    ~LinqNet();
    LinqNet* clone() const;
    void addUser(User*);
    void removeUser(Username*);
    int size() const;
    vector<SmartPtr<Username> > username() const;
    SmartPtr<User> operator[](const int&) const;
    friend ostream& operator<<(ostream&, const LinqNet&);
};
#endif