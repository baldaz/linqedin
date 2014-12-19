#ifndef SPUSER_H
#define SPUSER_H

#include "user.h"

class SPUser {
private:
    class RefCounter {
        int count;
    public:
        void addRef();
        int release();
    };
    User* _p_usr;
    RefCounter* ref;
public:
    SPUser(User*);
    SPUser(const SPUser&);
    ~SPUser();
    SPUser& operator=(const SPUser&);
    User& operator*() const;
    User* operator->() const;
    bool operator==(const SPUser&) const;
    bool operator!=(const SPUser&) const;
};

#endif