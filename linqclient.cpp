#include "linqclient.h"

using std::map;

LinqClient::LinqClient() : _db(new LinqDB()) {}
LinqClient::LinqClient(const Username& usr) : _db(new LinqDB) {
    _usr = _db->find(usr);
    if (_usr == NULL) throw Error(userNotFound, "User not found");
    if(_usr->account()->username() != usr) throw Error(userNotFound, "User not found");
}
LinqClient::~LinqClient() {delete _db;}
Username LinqClient::username() const {
    return _usr->account()->username();
}
Info* LinqClient::info() const {
    return _usr->account()->info();
}
int LinqClient::level() const {
    return _usr->account()->prLevel();
}
void LinqClient::addContact(const Username& usr) {
    _usr->addContact(_db->find(usr));
}
void LinqClient::removeContact(const Username& usr) {
    _usr->removeContact(usr);
}
void LinqClient::alterProfile(int field, const string& value) throw(Error) {
    Bio* ui = dynamic_cast<Bio*> (_usr->account()->info());
    if(ui) {
        switch(field) {
            case 0:
                ui->setName(value);
            break;
            case 1:
                ui->setSurname(value);
            break;
            case 2:
                ui->setAddress(value);
            break;
            case 3:
                ui->setBirthdate(QDate::fromString(QString::fromStdString(value), "dd.MM.yyyy"));
            break;
            case 4:
                ui->setEmail(value);
            break;
            case 5:
                ui->setTelephon(value);
            break;
            case 6:
                ui->setWebsite(value);
            break;
            case 7:
                ui->setBio(value);
            break;
            case 8: {
                list<SmartPtr<User> >::const_iterator it = _db->begin();
                bool alreadyIn = false;
                for(; it != _db->end() && !alreadyIn; ++it) {
                    if(((*it)->account()->username().login()) == value && _usr->account()->username().login() != value)
                        alreadyIn = true;
                }
                if(alreadyIn) throw Error(dupUser, "An user with that username already exists in Linqedin");
                else _usr->account()->username().setLogin(value);
            }
            break;
            case 9:
                if(!value.empty()) _usr->account()->username().setPassword(value);
            break;
        }
    }
}
void LinqClient::requestUpgrade(const string& code, const string& nominee, privLevel newlevel) throw(Error){
    if(code.empty() || nominee.empty()) throw Error(payment, "Nominee or code field cannot be empty");
    if(_usr->account()->lastPayment()->approvation()) {
        Username me = _usr->account()->username();
        Subscription s(newlevel);
        CreditCard card(nominee, code);
        bool app = false;
        if(newlevel == basic) {
            app = true;
            _usr->account()->setPrLevel(newlevel);
        }
        Payment p(&me, &s, &card, app);
        _usr->account()->addPayment(p);
    }
    else throw Error(payment, "There is already a subscription pending for approvation");
}
string LinqClient::displayHtmlInfo() const {
    string ret = _usr->showInfo();
    if(level() > basic) {
        list<Group*> ls = listGroups();
        if(ls.size() > 0) {
            ret += "<h4>Groups</h4><ul style='font-weight:400'>";
            for(list<Group*>::iterator j = ls.begin(); j != ls.end(); ++j)
                ret += "<li>" + (*j)->name() + "</li>";
            ret += "</ul>";
        }
    }
    return ret;
}
string LinqClient::avatarFromUser(const Username& u) const {
    User* x = _db->find(u);
    if(x) return x->account()->avatar().path();
    return STANDARD_AVATAR;
}
int LinqClient::netSize() const {
    return _usr->net()->size();
}
list<SmartPtr<User> > LinqClient::visitors() const {
    list<SmartPtr<User> > u;
    if(ExecutiveUser* p = dynamic_cast<ExecutiveUser*> (_usr))
        u = p->visitors();
    return u;
}
int LinqClient::userSimilarity(const SmartPtr<User>& u) const {
    return _usr->similarity(u);
}
vector<SmartPtr<User> > LinqClient::similarity() const {
    return _usr->listPossibleLinks(*_db);
}
bool LinqClient::linked(const Username& usr) const {
   return _usr->linked(usr);
}
vector<string> LinqClient::displayHtmlNet() const {
    vector<string> ret;
    string html = "";
    std::ostringstream o;
    o << _usr->net()->size();
    UserInfo* info;
    string name, surname;
    vector<Username> vec = _usr->net()->username();
    vector<Username>::const_iterator it = vec.begin();
    for(; it < vec.end(); ++it) {
        info = dynamic_cast<UserInfo*> ((_db->find(*it))->account()->info());
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
    vector<Username> vec = _usr->net()->username();
    vector<Username>::const_iterator it = vec.begin();
    User* acc;
    for(; it < vec.end(); ++it) {
        acc = _db->find(*it);
        ret.push_back(SmartPtr<User>(acc));
    }
    return ret;
}
vector<SmartPtr<Payment> > LinqClient::paymentHistory() const {
    return _usr->account()->history();
}
list<SmartPtr<Message> > LinqClient::inMail() const {
    return _usr->inMail();
}
list<SmartPtr<Message> > LinqClient::outMail() const {
    return _usr->outMail();
}
map<string, string> LinqClient::find(const string& wanted = "") const {
    return _usr->userSearch(*_db, wanted);
}
map<string, int> LinqClient::keywordFrequency() const {
    ExecutiveUser* tmp = dynamic_cast<ExecutiveUser*> (_usr);
    map<string, int> ret;
    if(tmp) ret = tmp->keywordPercent();
    return ret;
}
Group LinqClient::findGroup(const string& n) const {
    return _db->findGroupByName(n);
}
void LinqClient::addExperience(const Experience& xp) {
    UserInfo* uf = dynamic_cast<UserInfo*> (_usr->account()->info());
    if(uf) uf->addExperience(xp);
}
void LinqClient::removeExperience(const Experience& e) {
    UserInfo* ui = dynamic_cast<UserInfo*> (_usr->account()->info());
    if(ui) ui->removeExperience(e);
}
void LinqClient::addVisitTo(const Username& usr) {
    User* u = _db->find(usr);
    u->addVisit();
}
void LinqClient::save() const {
    _db->save();
}
string LinqClient::avatar() const {
    return _usr->account()->avatar().path();
}
void LinqClient::setAvatar(const string& path) {
    Avatar avt(path);
    _usr->account()->setAvatar(avt);
}
void LinqClient::sendMail(const string& dest, const string& obj, const string& body, bool read) throw(Error){
    Username dst(dest, "");
    User* recip = _db->find(dst);
    if(recip == NULL) throw Error(userNotFound, "Recipient not found, maybe it doesn't exists");
    Message mail(_usr->account()->username(), dst, obj, body, read);
    recip->loadInMail(mail);
    _usr->sendMessage(mail);
}
void LinqClient::deleteMessage(const Message& m) {
    _usr->deleteMessage(m);
}
int LinqClient::visitCount() const {
    return _usr->visitCount();
}
void LinqClient::modifyInMail(const list<SmartPtr<Message> >& l) {
    _usr->setInMail(l);
}
list<Group*> LinqClient::listGroups() const {
    list<Group*> ret;
    if(BusinessUser* bu = dynamic_cast<BusinessUser*> (_usr))
        ret = bu->groups();
    return ret;
}
list<Group*> LinqClient::listAllGroups() const {
    return _db->allGroups();
}
list<Group*> LinqClient::listUserGroups(const Username& u) const {
    list<Group*> ret;
    User* x = _db->find(u);
    if(BusinessUser* bu = dynamic_cast<BusinessUser*> (x))
        ret = bu->groups();
    return ret;
}
list<Post*> LinqClient::listPostFromGroup(const Group& g) const {
    return _db->postsFromGroup(g);
}
int LinqClient::postNumberFromGroup(const Group& g) const {
    return _db->postNumberFromGroup(g);
}
void LinqClient::addPostToGroup(const Group& g, const Post& p) {
    _db->addPostToGroup(g, p);
}
void LinqClient::createNewGroup(const Group& g) throw(Error) {
    if(dynamic_cast<ExecutiveUser*> (_usr))
        _db->addGroup(g);
    else throw Error(permission, "You must be at least Executive privileged to create a group");
}
void LinqClient::addGroup(const Group& g) {
    if(BusinessUser* bu = dynamic_cast<BusinessUser*> (_usr)) {
        bu->addGroup(g);
        _db->addMemberToGroup(g, username());
    }
}
void LinqClient::addGroup(const string& n, const string& a) {
    Group* g = new Group(Username(a, ""), n);
    addGroup(*g);
}
void LinqClient::leaveGroup(const string& name) {
    Group& g = _db->findGroupByName(name);
    if(BusinessUser* bu = dynamic_cast<BusinessUser*> (_usr))
        bu->removeGroup(g);
    _db->removeMemberFromGroup(g, username());
    _db->save();
}
void LinqClient::kickMember(const string& name, const string& u_name) {
    Group& g = _db->findGroupByName(name);
    _db->removeMemberFromGroup(g, Username(u_name, ""));
    _db->save();
}
void LinqClient::deleteGroup(const string& n) {
    Group* g = new Group(_db->findGroupByName(n));
    if(ExecutiveUser* ex = dynamic_cast<ExecutiveUser*> (_usr)) {
        ex->globalRemoveGroup(*_db, *g);
    }
    _db->deleteGroup(*g);
}
void LinqClient::clearPosts(const string& name) {
    Group& g = _db->findGroupByName(name);
    g.clearPosts();
}
int LinqClient::outMailCount() const {
    return _usr->outMailCount();
}
int LinqClient::outMailLimit() const {
    if(level() == basic)
        return BasicUser::basicLimit();
    else if(level() == business)
        return BusinessUser::businessLimit();
    else return -1;
}
// aggiunge una caratteristica alle info del client, 0 => skill, 1 => language, 2 => interest
void LinqClient::addTrait(int trait, const string& value) {
    UserInfo* ui = dynamic_cast<UserInfo*> (_usr->account()->info());
    switch(trait) {
        case 0:
            ui->addSkill(value);
        break;
        case 1:
            ui->addLanguage(value);
        break;
        case 2:
            ui->addInterest(value);
        break;
    }
}
// cancella una caratteristica dalle info del client, 0 => skill, 1 => language, 2 => interest
void LinqClient::deleteTrait(int trait, const string& value) {
    UserInfo* ui = dynamic_cast<UserInfo*> (_usr->account()->info());
    switch(trait) {
        case 0:
            ui->removeSkill(value);
        break;
        case 1:
            ui->removeLanguage(value);
        break;
        case 2:
            ui->removeInterest(value);
        break;
    }
}
