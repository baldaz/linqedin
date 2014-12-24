#include "linqadmin.h"

LinqAdmin::completeRemove::completeRemove(Username* usr) : rmusr(usr) {}
LinqAdmin::completeRemove::~completeRemove() { }
void LinqAdmin::completeRemove::operator()(const SmartPtr<User>& user) const {
    user->removeContact(rmusr);
}
LinqAdmin::LinqAdmin() : _db(new LinqDB()) {}
LinqAdmin::~LinqAdmin() { delete _db; }
void LinqAdmin::insertUser(User* newuser) {
    _db->addUser(newuser);
    save();
}
void LinqAdmin::removeUser(Username* user) {
    std::for_each(_db->begin(), _db->end(), completeRemove(user));
    _db->removeUser(user);
    save();
}
void alterSubscription(Username* usr, privLevel newlevel) {}
void LinqAdmin::find() const {}
void LinqAdmin::save() const {
    _db->save();
}