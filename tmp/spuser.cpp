#include "spuser.h"

void SPUser::RefCounter::addRef() {
    count++;
}
int SPUser::RefCounter::release() {
    return --count;
}
SPUser::SPUser(User* usr) : _p_usr(usr), ref(0) {
    ref = new RefCounter();
    ref->addRef();
}
SPUser::SPUser(const SPUser& spusr) : _p_usr(spusr._p_usr), ref(spusr.ref) {
    ref->addRef();
}
SPUser::~SPUser() {
    if(!ref->release()) {
        delete _p_usr;
        delete ref;
    }
}
SPUser& SPUser::operator=(const SPUser& spusr) {
    if (this != &spusr) {
        if(ref->release() == 0) {
            delete _p_usr;
            delete ref;
        }
        _p_usr = spusr._p_usr;
        ref = spusr.ref;
        ref->addRef();
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