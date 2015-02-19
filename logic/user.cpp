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
    if(outMailCount() < basicMailLimit)
        loadOutMail(mex);
    else throw Error(permission, "Mail limit for basic user reached, wait for monthly reset");
}
int BasicUser::basicLimit() {
    return basicMailLimit;
}
int BasicUser::basicMailLimit = 10;

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
BusinessUser::linkedWith::linkedWith(int s = 0, BusinessUser* usr = 0) : _offset(s), _owner(usr) {}
void BusinessUser::linkedWith::operator()(const SmartPtr<User>& spu) {
    if(!_owner->linked((spu->account()->username())) && (spu->account()->username()) != (_owner->account()->username()))
        if(_owner->similarity(spu) >= _offset)
            _mates.push_back(spu);
}
vector<SmartPtr<User> > BusinessUser::linkedWith::result() const {
    return _mates;
}
User* BusinessUser::clone() const {
    return new BusinessUser(*this);
}
map<string, string> BusinessUser::userSearch(const LinqDB& db, const string& wanted) const {
    return std::for_each(db.begin(), db.end(), searchFunctor(2, wanted, this)).result();
}
void BusinessUser::sendMessage(const Message& mex) throw(Error) {
    if(outMailCount() < businessMailLimit)
        loadOutMail(mex);
    else throw Error(permission, "Mail limit for business user reached, wait for monthly reset");
}
int BusinessUser::similarity(const SmartPtr<User>& user) const {
    UserInfo* uf = dynamic_cast<UserInfo*> (this->account()->info());
    UserInfo* host = dynamic_cast<UserInfo*> (user->account()->info());
    int i_w = 2, s_w = 6, l_w = 2;
    double counter = 0;
    // interests
    vector<string> interests = uf->interests();
    vector<string> h_interests = host->interests();
    if(interests.size() <= h_interests.size()) {
        vector<string>::const_iterator it = interests.begin();
        for(; it < interests.end(); ++it)
            if(std::find(h_interests.begin(), h_interests.end(), (*it)) != h_interests.end()) counter++;
        counter = (counter / h_interests.size()) * 100;
    }
    else {
        vector<string>::const_iterator ith = h_interests.begin();
        for(; ith < h_interests.end(); ++ith)
            if(std::find(interests.begin(), interests.end(), (*ith)) != interests.end()) counter++;
        counter = (counter / interests.size()) * 100;
    }
    double countsk = 0;
    // skills
    vector<string> skills = uf->skills();
    vector<string> h_skills = host->skills();
    if(skills.size() <= h_skills.size()) {
        vector<string>::const_iterator it = skills.begin();
        for(; it < skills.end(); ++it)
            if(std::find(h_skills.begin(), h_skills.end(), (*it)) != h_skills.end()) countsk++;
        countsk = (countsk / h_skills.size()) * 100;
    }
    else {
        vector<string>::const_iterator ith = h_skills.begin();
        for(; ith < h_skills.end(); ++ith)
            if(std::find(skills.begin(), skills.end(), (*ith)) != skills.end()) countsk++;
        countsk = (countsk / skills.size()) * 100;
    }
    double countl = 0;
    // language
    vector<string> languages = uf->languages();
    vector<string> h_languages = host->languages();
    if(languages.size() <= h_languages.size()) {
        vector<string>::const_iterator it = languages.begin();
        for(; it < languages.end(); ++it)
            if(std::find(h_languages.begin(), h_languages.end(), (*it)) != h_languages.end()) countl++;
        countl = (countl / h_languages.size()) * 100;
    }
    else {
        vector<string>::const_iterator ith = h_languages.begin();
        for(; ith < h_languages.end(); ++ith)
            if(std::find(languages.begin(), languages.end(), (*ith)) != languages.end()) countl++;
        countl = (countl / languages.size()) * 100;
    }
    double res;
    res = ((counter * i_w) + (countsk * s_w) + (countl * l_w)) / (i_w + s_w + l_w);
    return static_cast<int> (res);
}
vector<SmartPtr<User> > BusinessUser::listPossibleLinks(const LinqDB& db) const {
    return std::for_each(db.begin(), db.end(), linkedWith(45, const_cast<BusinessUser*> (this))).result();
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
int BusinessUser::businessLimit() {
    return businessMailLimit;
}
int BusinessUser::businessMailLimit = 25;

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
bool ExecutiveUser::removeVisitorOccurences(const SmartPtr<User>& s) {
    bool found = false;
    for(list<SmartPtr<User> >::iterator it = _visitors.begin(); it != _visitors.end() && !found; ++it)
        if((*it)->account()->username().login() == s->account()->username().login()) {
            _visitors.erase(it);
            found = true;
        }
    return found;
}
list<SmartPtr<User> > ExecutiveUser::visitors() const {
    return _visitors;
}
