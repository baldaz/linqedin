#ifndef LINQCLIENT_H
#define LINQCLIENT_H

#include "user.h"
#include "linqnet.h"

class LinqClient {
private:
    User* _usr;
    LinqDB* _db;
public:
    LinqClient();
    LinqClient(Username);
    void displayProfile() const;
    void alterProfile();
    void addFriend();
    void removeFriend();
    void find();
};
#endif