#ifndef LOADER_H
#define LOADER_H

#include "username.h"

class LinqClient;
class LinqAdmin;
class LinqDB;

class Loader {
private:
    LinqDB* _db;
public:
    Loader();
    ~Loader();
    bool isAdmin(const Username&) const;
    LinqClient* getClientHandle(const Username&) const;
    LinqAdmin* getAdminHandle() const;
};
#endif