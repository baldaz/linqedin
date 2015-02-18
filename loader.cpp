#include "loader.h"
#include "linqdb.h"
#include "linqclient.h"

Loader::Loader() : _db(new LinqDB()) {}
Loader::~Loader() { delete _db; }
bool Loader::isAdmin(const Username& u) const {
    if(_db->getAdmin() == u)
        return true;
    return false;
}
LinqClient* Loader::getClientHandle(const Username& u) const {
    return new LinqClient(u);
}