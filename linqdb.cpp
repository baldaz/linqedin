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
int LinqDB::getSize() const {
    return _db.size();
}
void LinqDB::addUser(const User& u) {
    SPUser spu(new User(u));
    _db.push_back(spu);
    // _db.insert(spu);
}
void LinqDB::removeUser(const User& usr) {
    for(int i = 0; i < this->getSize(); i++) {
        if(_db[i]->getUsername()->getLogin() == usr.getUsername()->getLogin())
            _db.erase(_db.begin() + i);
    }
}
LinqDB::SPUser LinqDB::operator[](const int& i) const {
    return _db[i];
}
ostream& operator<<(ostream& os, const LinqDB& db) {
    if(!db.getSize()) os << "Nessun utente inserito" << endl;
    else {
        for(int i = 0; i < db.getSize(); ++i){
            os << db[i]->getUsername()->getLogin() << " : ";
            os << db[i]->getUsername()->getPassword() << endl;
        }
        os << "DB size: " << db.getSize() << endl;
    }
    return os;
    // // if(!db._db.size()) os << "Nessun utente inserito" << endl;
    // // else {
    // //     for(db._db::iterator it = db._db.begin(); it != db._db.end(); ++it) {
    // //         os << *it->getUsername()->getLogin() << " : ";
    // //         os << *it->getUsername()->getPassword() << endl;
    // //     }
    // // }
    // return os;
}