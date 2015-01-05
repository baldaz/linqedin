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
void LinqAdmin::removeUser(const Username& user) {
    std::for_each(_db->begin(), _db->end(), completeRemove(const_cast<Username*> (&user)));
    _db->removeUser(const_cast<Username*> (&user));
    save();
}
void LinqAdmin::alterSubscription(const Username& usr, privLevel newlevel) {
    User* current = _db->find(const_cast<Username*> (&usr));
    current->account()->setPrLevel(newlevel);
    save();
}
void LinqAdmin::find() const {}
void LinqAdmin::save() const {
    _db->save();
}