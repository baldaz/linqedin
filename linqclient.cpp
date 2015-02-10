#include "linqclient.h"

using std::map;

LinqClient::LinqClient() : _db(new LinqDB()) {}
LinqClient::LinqClient(const Username& usr) : _db(new LinqDB) {
    _usr = _db->find(usr);
    if (_usr == NULL) throw Error(userNotFound, "User not found");
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
void LinqClient::alterProfile(int field, const string& value) {
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
            case 8:
                _usr->account()->username().setLogin(value);
            break;
            case 9:
                if(!value.empty()) _usr->account()->username().setPassword(value);
            break;
        }
    }
}
string LinqClient::displayProfile() const {
    std::string profile = "";
    std::ostringstream o, o2;
    o << _usr->account()->prLevel();
    o2 << *_usr->net();
    profile += "Account type >> " + o.str() + "\n";
    profile += "Credentials >> user: " + _usr->account()->username().login() + "  password: " + _usr->account()->username().password() + "\n";
    profile += "Account info >> " + _usr->account()->info()->print() + "\n";
    profile += "Friend list >> ";
    profile += o2.str() + "\n";
    profile += "inMail >> ";
    list<SmartPtr<Message> > inm = _usr->inMail();
    list<SmartPtr<Message> > outm = _usr->outMail();
    list<SmartPtr<Message> >::const_iterator it = inm.begin();
    for(; it != inm.end(); ++it)
        profile += "Sender: " + (*it)->sender().login() + " Receiver: " + (*it)->receiver().login() + "\n";
    return profile;
}
string LinqClient::displayHtmlInfo() const {
    return _usr->showInfo();
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
vector<SmartPtr<User> > LinqClient::similarity() const {
    return _usr->listPossibleLinks(*_db);
}
bool LinqClient::linked(const Username& usr) const {
   return _usr->linked(usr);
}
vector<string> LinqClient::skills() const {
    vector<string> ret;
    if(UserInfo* p = dynamic_cast<UserInfo*> (_usr->account()->info()))
        ret = p->skills();
    return ret;
}
vector<string> LinqClient::interests() const {
    vector<string> ret;
    if(UserInfo* p = dynamic_cast<UserInfo*> (_usr->account()->info()))
        ret = p->interests();
    return ret;
}
vector<string> LinqClient::languages() const {
    vector<string> ret;
    if(UserInfo* p = dynamic_cast<UserInfo*> (_usr->account()->info()))
        ret = p->languages();
    return ret;
}
list<Experience*> LinqClient::experiences() const {
    list<Experience*> ret;
    if(UserInfo* p = dynamic_cast<UserInfo*> (_usr->account()->info()))
        ret = p->experiences();
    return ret;
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
list<Group*> LinqClient::listGroups() const {
    list<Group*> ret;
    if(BusinessUser* bu = dynamic_cast<BusinessUser*> (_usr))
        ret = bu->groups();
    return ret;
}
list<Group*> LinqClient::listAllGroups() const {
    return _db->allGroups();
}
list<Post*> LinqClient::listPostFromGroup(const Group& g) const {
    return _db->postsFromGroup(g);
}
int LinqClient::postNumberFromGroup(const Group& g) const {
    return _db->postNumberFromGroup(g);
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
    return _db->findGroubByName(n);
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
    // _usr->account()->avatar().setPath(path);
    Avatar avt(path);
    _usr->account()->setAvatar(avt);
}
void LinqClient::sendMail(const string& dest, const string& obj, const string& body, bool read) {
    Username* dst = new Username(dest, "");
    User* recip = _db->find(*dst);
    Message* mail = new Message(_usr->account()->username(), *dst, obj, body, read);
    recip->loadInMail(*mail);
    _usr->sendMessage(*mail);
    delete dst;
    delete mail;
}
int LinqClient::visitCount() const {
    return _usr->visitCount();
}
void LinqClient::modifyInMail(const list<SmartPtr<Message> >& l) {
    _usr->setInMail(l);
}
void LinqClient::addPostToGroup(const Group& g, const Post& p) {
    // if(BusinessUser* bu = dynamic_cast<BusinessUser*> (_usr))
    //     bu->addPost(g, p);
    _db->addPostToGroup(g, p);
}
void LinqClient::createNewGroup(const Group& g) {
    if(dynamic_cast<ExecutiveUser*> (_usr))
        _db->addGroup(g);
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
void LinqClient::deleteGroup(const string& n, const string& a) {
    Group* g = new Group(Username(a, ""), n);
    // _db->deleteGroup(*g);
    if(ExecutiveUser* ex = dynamic_cast<ExecutiveUser*> (_usr))
        ex->globalRemoveGroup(*_db, *g);
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
// modifica una caratteristica nelle indo del client, 0 => skill, 1 => language, 2 => interest
// void LinqClient::modifyTrait(int trait, const string& value) {
//     UserInfo* ui = dynamic_cast<UserInfo*> (_usr->account()->info());
//     switch(trait) {
//         case 0:
//             ui->modifySkill(value);
//         break;
//         case 1:
//             ui->modifyLanguage(value);
//         break;
//         case 2:
//             ui->modifyInterest(value);
//         break;
//     }
// }
