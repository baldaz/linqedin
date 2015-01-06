#include "linqclient.h"

LinqClient::LinqClient() : _db(new LinqDB()){}
LinqClient::LinqClient(const Username& usr) : _db(new LinqDB) {
    _usr = _db->find(const_cast<Username*> (&usr));
}
LinqClient::~LinqClient() {delete _usr; delete _db; }
void LinqClient::addContact(const Username& usr) {
    _usr->addContact(_db->find(const_cast<Username*> (&usr)));
}
void LinqClient::removeContact(const Username& usr) {
    _usr->removeContact(const_cast<Username*> (&usr));
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
string LinqClient::displayHtmlInfo() const {
    return _usr->account()->info()->printHtml();
}
int LinqClient::netSize() const {
    return _usr->net()->size();
}
vector<string> LinqClient::displayHtmlNet() const {
    vector<string> ret;
    string html = "";
    std::ostringstream o;
    o << _usr->net()->size();
    UserInfo* info;
    string name, surname;
    vector<SmartPtr<Username> > vec = _usr->net()->username();
    vector<SmartPtr<Username> >::const_iterator it = vec.begin();
    for(; it < vec.end(); ++it) {
        info = dynamic_cast<UserInfo*> ((_db->find(&(**it)))->account()->info());
        if(info) {
            name = info->name();
            surname = info->surname();
        }
        html = name + " " + surname;
        ret.push_back(html);
    }
    return ret;
}
vector<SmartPtr<User> > LinqClient::contactsInfo() const {
    vector<SmartPtr<User> > ret;
    vector<SmartPtr<Username> > vec = _usr->net()->username();
    vector<SmartPtr<Username> >::const_iterator it = vec.begin();
    User* acc;
    for(; it < vec.end(); ++it) {
        acc = _db->find(&(**it));
        ret.push_back(SmartPtr<User>(acc));
    }
    return ret;
}
string LinqClient::find(string wanted = "") const {
    return _usr->userSearch(*_db, wanted);
}
void LinqClient::addExperience(const Experience& xp) {
    UserInfo* uf = dynamic_cast<UserInfo*> (_usr->account()->info());
    if(uf) uf->addExperience(const_cast<Experience*> (&xp));
}
void LinqClient::addFormation(const Experience& frm) {
    UserInfo* uf = dynamic_cast<UserInfo*> (_usr->account()->info());
    if(uf) uf->addFormation(const_cast<Experience*> (&frm));
}
void LinqClient::save() const {
    _db->save();
}