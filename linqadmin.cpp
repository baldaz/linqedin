#include "linqadmin.h"

LinqAdmin::completeRemove::completeRemove(const Username& usr) : rmusr(usr) {}
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
void LinqAdmin::insertUser(const string& username, const string& password, const map<string, string>& info) {
    string name = (info.find("name"))->second;
    string surname = info.find("surname")->second;
    string address = info.find("address")->second;
    string phone = info.find("telephone")->second;
    string website = info.find("website")->second;
    string email = info.find("e-mail")->second;
    string birthdate = info.find("birthdate")->second;
    string bio = info.find("bio")->second;
    Bio b(name, surname, email, address, phone, website, QDate::fromString(QString::fromStdString(birthdate), "dd.MM.yyyy"), bio);
    Username u(username, password);
    Account a(&b, u, basic);
    BasicUser nu(&a);
    this->insertUser(&nu);
}
void LinqAdmin::removeUser(const Username& user) {
    std::for_each(_db->begin(), _db->end(), completeRemove(user));
    _db->removeUser(user);
    save();
}
void LinqAdmin::alterSubscription(const Username& usr, privLevel newlevel) {
    User* current = _db->find(usr);
    current->account()->setPrLevel(newlevel);
    save();
}
void LinqAdmin::find() const {}
void LinqAdmin::save() const {
    _db->save();
}