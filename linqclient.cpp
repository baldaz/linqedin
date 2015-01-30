#include "linqclient.h"

using std::map;

LinqClient::LinqClient() : _db(new LinqDB()), _avatar(STANDARD_AVATAR) {}
LinqClient::LinqClient(const Username& usr) : _db(new LinqDB), _avatar(STANDARD_AVATAR)  {
    _usr = _db->find(usr);
}
LinqClient::~LinqClient() {delete _db;}
Username LinqClient::username() const {
    return _usr->account()->username();
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
void LinqClient::alterProfile(const map<int, string>& changes) {
    // map<int, string>::iterator it = changes.begin();
    // for(; it != changes.begin(); ++it) {
    //     switch(it->first) {
    //         case 0:

    //     }
    // }
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
    return _usr->account()->info()->printHtml();
}
string LinqClient::displayHtmlPayments() const {
    vector<SmartPtr<Payment> > v = _usr->account()->history();
    return "<html><table><tr><th style='padding:10px;'>Subscription</th><th style='padding:10px;'>Method</th><th style='padding:10px'>Amount</th></tr></table></html>";
}
string LinqClient::displayHtmlSettings() const {
    string html = "";
    html = "<html>";
    html += "<h3> Username</h3><p style='font-weight:400;'>" + _usr->account()->username().login() + "</p>";
    html += "<h3> Account type</h3><p style='font-weight:400;'>" + utilities::Utils::levelToString(_usr->account()->prLevel()) + "</p></html>";
    return html;
}
string LinqClient::displayHtmlMessages() const {
    return "<html><table><tr><th style='padding:10px;'>Subject</th><th style='padding:10px;'>Body</th><th style='padding:10px'>From</th></tr></table></html>";
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
    // ExecutiveUser* eu = dynamic_cast<ExecutiveUser*> (_usr);
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
list<SmartPtr<Message> > LinqClient::inMail() const {
    return _usr->inMail();
}
list<SmartPtr<Message> > LinqClient::outMail() const {
    return _usr->outMail();
}
list<Group*> LinqClient::listGroups() const {
    if(BusinessUser* bu = dynamic_cast<BusinessUser*> (_usr))
        return bu->groups();
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
    if(tmp) {
        ret = tmp->keywordPercent();
        return ret;
    }
}
Group LinqClient::findGroup(const string& n) const {
    return _db->findGroubByName(n);
}
void LinqClient::addExperience(const Experience& xp) {
    UserInfo* uf = dynamic_cast<UserInfo*> (_usr->account()->info());
    if(uf) uf->addExperience(xp);
}
void LinqClient::addVisitTo(const Username& usr) {
    User* u = _db->find(usr);
    u->addVisit();
}
void LinqClient::save() const {
    _db->save();
}
string LinqClient::avatar() const {
    return _avatar;
}
void LinqClient::setAvatar(const string& path) {
    _avatar = path;
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