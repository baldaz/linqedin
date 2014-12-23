#include "linqadmin.h"

LinqAdmin::LinqAdmin() : _db(new LinqDB()) {}
LinqAdmin::~LinqAdmin() { delete _db; }
void LinqAdmin::insertUser(User* newuser) {
    _db->addUser(newuser);
}
void LinqAdmin::removeUser(Username* user) {
    _db->removeUser(user);
}
void alterSubscription(Username* usr, privLevel newlevel) {}
void LinqAdmin::find() const {}
void LinqAdmin::save() const {
    _db->save();
}