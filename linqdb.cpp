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