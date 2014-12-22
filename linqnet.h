#ifndef LINQNET_H
#define LINQNET_H

#include <iostream>
#include <vector>
#include "spuser.h"

using std::vector;
using std::ostream;

class LinqNet {
private:
    vector<SPUser> _net;
public:
    ~LinqNet();
    // LinqNet* clone() const;
    void addUser(User*);
    void removeUser(User*);
    int size() const;
    vector<Username*> username() const;
    SPUser operator[](const int&) const;
    friend ostream& operator<<(ostream&, const LinqNet&);
};
#endif