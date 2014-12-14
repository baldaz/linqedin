#include "spuser.h"

SPUser::SPUser(User* usr) : _p_usr(usr) {
    if(_p_usr)
        _p_usr->references++;
}
SPUser::SPUser(const SPUser& spusr) : _p_usr(spusr._p_usr) {
    if(_p_usr)
        _p_usr->references++;
}
SPUser::~SPUser() {
    if(_p_usr) {
        _p_usr->references--;
        if(!_p_usr->references)
            delete _p_usr;
    }
}
SPUser& SPUser::operator=(const SPUser& spusr) {
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
User& SPUser::operator*() const {
    return *_p_usr;
}
User* SPUser::operator->() const {
    return _p_usr;
}
bool SPUser::operator==(const SPUser& spu) const{
    return(_p_usr == spu._p_usr);
}
bool SPUser::operator!=(const SPUser& spu) const{
    return(_p_usr != spu._p_usr);
}