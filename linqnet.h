#ifndef LINQNET_H
#define LINQNET_H

#include <iostream>
#include <vector>
#include "user.h"

using std::vector;
using std::ostream;

class LinqNet {
private:
    vector<SmartPtr<User> > _net;
public:
    ~LinqNet();
    LinqNet* clone() const;
    void addUser(User*);
    void removeUser(const Username&);
    int size() const;
    vector<SmartPtr<Username> > username() const;
    SmartPtr<User> operator[](const int&) const;
    string printHtml() const;
    friend ostream& operator<<(ostream&, const LinqNet&);
};
#endif