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
    _usr->removeContact(_db->find(usr));
}
void LinqClient::displayProfile() const {
    std::cout << _usr->account()->username()->login().toStdString() << " - " << _usr->account()->username()->password().toStdString() << std::endl;
    std::cout << _usr->net()->size() << std::endl;
}