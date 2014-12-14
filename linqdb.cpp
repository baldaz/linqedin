#include "linqdb.h"

LinqDB::SPUser::SPUser(User* usr) : _p_usr(usr) {
    if(_p_usr)
        _p_usr->references++;
}
LinqDB::SPUser::SPUser(const SPUser& spusr) : _p_usr(spusr._p_usr) {
    if(_p_usr)
        _p_usr->references++;
}
LinqDB::SPUser::~SPUser() {
    if(_p_usr) {
        _p_usr->references--;
        if(!_p_usr->references)
            delete _p_usr;
    }
}
LinqDB::SPUser& LinqDB::SPUser::operator=(const SPUser& spusr) {
    if(this != &spusr) {
        User* u = _p_usr;
        _p_usr = spusr._p_usr;
        if(_p_usr) _p_usr->references++;
        if(u) {
            u->references--;
            if(!u->references) delete u;
        }
    }
    return *this;
}
LinqDB::SPUser::User& LinqDB::SPUser::operator*() const {
    return *_p_usr;
}
LinqDB::User* LinqDB::SPUser::operator->() const {
    return _p_usr;
}
bool LinqDB::SPUser::operator==(const SPUser& spu) {
    return(_p_usr == spu._p_usr);
}
bool LinqDB::SPUser::operator!=(const SPUser& spu) {
    return(_p_usr != spu._p_usr);
}