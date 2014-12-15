#include "linqdb.h"

using std::ostream;
using std::endl;

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
User& LinqDB::SPUser::operator*() const {
    return *_p_usr;
}
User* LinqDB::SPUser::operator->() const {
    return _p_usr;
}
bool LinqDB::SPUser::operator==(const SPUser& spu) const {
    return(_p_usr == spu._p_usr);
}
bool LinqDB::SPUser::operator!=(const SPUser& spu) const {
    return(_p_usr != spu._p_usr);
}
/* parte db */
void LinqDB::addUser(const User& u) {
    SPUser spu(new User(u));
    _db.push_back(spu);
}
ostream& operator<<(ostream& os, const LinqDB& db) {
    if(!db._db.size()) os << "Nessun utente inserito" << endl;
    else {
        for(int i = 0; i < db._db.size(); ++i){
            os << db._db[i]->getUsername()->getLogin() << " : ";
            os << db._db[i]->getUsername()->getPassword() << endl;
        }
        os << "DB size: " << db._db.size() << endl;
    }
    return os;
}