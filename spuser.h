#ifndef SPUSER_H
#define SPUSER_H

#include "user.h"

class SPUser {
private:
    User* _p_usr;
public:
    SPUser(User* =0);
    SPUser(const SPUser&);
    ~SPUser();
    SPUser& operator=(const SPUser&);
    User& operator*() const;
    User* operator->() const;
    bool operator==(const SPUser&) const;
    bool operator!=(const SPUser&) const;
};

#endif