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
void LinqClient::displayProfile() const {
    std::cout << "Account type >> " << _usr->account()->prLevel() << std::endl;
    std::cout << "Credentials >> " << _usr->account()->username()->login().toStdString() << " - " << _usr->account()->username()->password().toStdString() << std::endl;
    std::cout << "DB size >> " << _db->size() << " Friends >> " << _usr->net()->size() << std::endl;
    std::cout << "Account info >> " << _usr->account()->info()->print().toStdString() << std::endl;
    std::cout << "Friend list >> ";
    std::cout << *_usr->net() << std::endl;
}
void LinqClient::find() const {
    _usr->userSearch(*_db);
}