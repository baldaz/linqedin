#include "user.h"
#include "linqdb.h"

BasicUser::BasicUser(Account* ac) : User(ac){}
BasicUser::BasicUser(const BasicUser& usr) : User(usr){}
BasicUser& BasicUser::operator=(const BasicUser& b) {
    if(this != &b)
        this->User::operator=(b);
    return *this;
}
User* BasicUser::clone() const {
    return new BasicUser(*this);
}
map<string, string> BasicUser::userSearch(const LinqDB& db, const string& wanted) const {
    return std::for_each(db.begin(), db.end(), searchFunctor(1, wanted, this)).result();
}
void BasicUser::sendMessage(const Message& mex) throw(Error) {
    if((unsigned) outMailCount() < basicMailLimit)
        loadOutMail(mex);
    else throw Error(permission, "Mail limit for basic user reached, wait for monthly reset");
}
unsigned int BasicUser::basicLimit() {
    return basicMailLimit;
}
unsigned int BasicUser::basicMailLimit = 10;

BusinessUser::BusinessUser(Account* ac) : BasicUser(ac) {}
BusinessUser::BusinessUser(const BusinessUser& usr) : BasicUser(usr) {
    for (list<Group*>::const_iterator i = (usr._groups).begin(); i != (usr._groups).end(); ++i)
        _groups.push_back(new Group(**i));
}
BusinessUser& BusinessUser::operator=(const BusinessUser& b) {
    if(this != &b) {
        for(list<Group*>::iterator i = _groups.begin(); i != _groups.end(); ++i)
            delete *i;
        _groups.clear();
       this->BasicUser::operator=(b);
        _groups = b._groups;
    }
    return *this;
}
BusinessUser::~BusinessUser() {
    if(!_groups.empty()) {
        for(list<Group*>::iterator i = _groups.begin(); i != _groups.end(); ++i)
            delete *i;
        _groups.clear();
    }
}
User* BusinessUser::clone() const {
    return new BusinessUser(*this);
}
map<string, string> BusinessUser::userSearch(const LinqDB& db, const string& wanted) const {
    return std::for_each(db.begin(), db.end(), searchFunctor(2, wanted, this)).result();
}
void BusinessUser::sendMessage(const Message& mex) throw(Error) {
    if((unsigned) outMailCount() < businessMailLimit)
        loadOutMail(mex);
    else throw Error(permission, "Mail limit for business user reached, wait for monthly reset");
}
list<Group*> BusinessUser::groups() const {
    return _groups;
}
void BusinessUser::addGroup(const Group& g) throw(Error){
    bool found = false;
    list<Group*>::iterator it = _groups.begin();
    for(; it != _groups.end() && !found; ++it)
        if((**it) == g) found = true;
    if(!found) _groups.push_back(const_cast<Group*> (&g)); // controllo gruppi duplicati
    else throw Error(dupGroup, "Already member of this group");
}
void BusinessUser::removeGroup(const Group& g) {
    bool found = false;
    list<Group*>::iterator it = _groups.begin();
    for(; it != _groups.end() && !found; ++it)
        if((**it) == g) {
            delete *it;
            _groups.erase(it);
            found = true;
        }
}
void BusinessUser::addBio(const string& bio) const {
    if(Bio* b = dynamic_cast<Bio*> (this->account()->info())) {
        b->setBio(bio);
        this->account()->setInfo(b);
    }
}
unsigned int BusinessUser::businessLimit() {
    return businessMailLimit;
}
unsigned int BusinessUser::businessMailLimit = 25;

ExecutiveUser::RemoveGroup::RemoveGroup(Group* g) : gr(g) {}
void ExecutiveUser::RemoveGroup::operator()(const SmartPtr<User>& u) {
    if(BusinessUser* ex = dynamic_cast<BusinessUser*> (&(*u))) {
        list<Group*> lu = ex->groups();
        list<Group*>::iterator it = lu.begin();
        for(; it != lu.end(); ++it) {
            if((**it) == *gr)
                ex->removeGroup(**it);
        }
    }
}
ExecutiveUser::ExecutiveUser(Account* ac) : BusinessUser(ac) {}
ExecutiveUser::ExecutiveUser(const ExecutiveUser& usr) : BusinessUser(usr), _keywords(usr._keywords), _visitors(usr._visitors) {}
ExecutiveUser::~ExecutiveUser() {_keywords.clear(); _visitors.clear();}
ExecutiveUser& ExecutiveUser::operator=(const ExecutiveUser& e) {
    if(this != &e) {
        _visitors.clear();
        _keywords.clear();
        this->BusinessUser::operator=(e);
        _visitors = e._visitors;
        _keywords = e._keywords;
    }
    return *this;
}
User* ExecutiveUser::clone() const {
    return new ExecutiveUser(*this);
}
map<string, string> ExecutiveUser::userSearch(const LinqDB& db, const string& wanted) const {
    return std::for_each(db.begin(), db.end(), searchFunctor(3, wanted, this)).result();
}
void ExecutiveUser::sendMessage(const Message& mex) throw(Error) {
    loadOutMail(mex);
}
void ExecutiveUser::addKeyword(const string& key) {
    ++_keywords[key];
}
void ExecutiveUser::globalRemoveGroup(const LinqDB& db, const Group& g) {
    std::for_each(db.begin(), db.end(), RemoveGroup(const_cast<Group*> (&g)));
    removeGroup(g);
}
map<string, int> ExecutiveUser::keywordPercent() const {
    map<string, int> ret;
    int sum = 0;
    map<string, int>::const_iterator itr = _keywords.begin();
    for(; itr != _keywords.end(); ++itr)
        sum += itr->second;
    map<string, int>::const_iterator it = _keywords.begin();
    double res;
    for(; it != _keywords.end(); ++it) {
        res = (static_cast<double> (it->second) / sum) * 100;
        ret.insert(std::pair<string, int>(it->first, static_cast<int>(res)));
    }
    return ret;
}
map<string, int> ExecutiveUser::keywords() const {
    return _keywords;
}
void ExecutiveUser::addVisitor(const SmartPtr<User>& v) {
    if(_visitors.size() < 10)
        _visitors.push_front(v);
    else if(_visitors.size() == 10) {
        _visitors.pop_back();
        _visitors.push_front(v);
    }
}
list<SmartPtr<User> > ExecutiveUser::visitors() const {
    return _visitors;
}
