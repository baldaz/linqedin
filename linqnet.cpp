#include "linqnet.h"

void LinqNet::addUser(const User& usr) {
    SPUser spu(new User(usr));
    _net.push_back(spu);
}