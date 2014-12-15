#ifndef LINQNET_H
#define LINQNET_H

#include <vector>
#include "spuser.h"

using std::vector;

class LinqNet {
private:
    vector<SPUser> _net;
public:
    void addUser(const User&);
    void delUser(const User&);
    int getSize() const;
    SPUser operator[](const int&) const;
    friend ostream& operator<<(ostream&, const LinqNet&);
};
#endif