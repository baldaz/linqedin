#include "linqclient.h"

LinqClient::LinqClient() : _db(new LinqDB()){}
LinqClient::LinqClient(Username* usr) : _db(new LinqDB) {
    _usr = _db->find(usr);
}
LinqClient::~LinqClient() { delete _usr; delete _db; }
void LinqClient::addContact(Username* usr) {
    _usr->addContact(_db->find(usr));
}
void LinqClient::removeContact(Username* usr) {
    _usr->removeContact(usr);
}
string LinqClient::displayProfile() const {
    std::string profile = "";
    std::ostringstream o, o2;
    o << _usr->account()->prLevel();
    o2 << *_usr->net();
    profile += "Account type >> " + o.str() + "\n";
    profile += "Credentials >> user: " + _usr->account()->username()->login() + "  password: " + _usr->account()->username()->password() + "\n";
    // profile += "DB size >> " + _db->size() + " Friends >> " + _usr->net()->size() + "\n";
    profile += "Account info >> " + _usr->account()->info()->print() + "\n";
    profile += "Friend list >> ";
    profile += o2.str() + "\n";
    return profile;
}
void LinqClient::find() const {
    _usr->userSearch(*_db);
}
void LinqClient::addExperience(Experience* xp) {
    UserInfo* uf;
    uf = dynamic_cast<UserInfo*> (_usr->account()->info());
    if(uf) uf->addExperience(xp);
}
void LinqClient::addFormation(Experience* frm) {
    UserInfo* uf;
    uf = dynamic_cast<UserInfo*> (_usr->account()->info());
    if(uf) uf->addFormation(frm);
}
void LinqClient::save() const {
    _db->save();
}