#include "user.h"
#include "linqnet.h"
#include "linqdb.h"
#include "utils.h"
#include <sstream>

using std::vector;
using std::map;

User::User(Account* ac) : _acc(ac->clone()), _net(new LinqNet()), _visitcount(0) {}
User::User(const User& usr) : _acc(usr._acc->clone()), _net(usr._net->clone()), _visitcount(usr._visitcount), _inMail(usr._inMail), _outMail(usr._outMail) {}
User::~User() {
    delete _acc;
    delete _net;
    _inMail.clear();
    _outMail.clear();
}
User& User::operator=(const User& usr) {
    if(this != &usr) {
        delete _acc;
        delete _net;
        _acc = usr._acc->clone();
        _net = usr._net->clone();
        _visitcount = usr._visitcount;
        _inMail = usr._inMail;
        _outMail = usr._outMail;
    }
    return *this;
}

User::searchFunctor::searchFunctor(int s = 0, const string& w = "", const User* call = 0) : _s_type(s), _wanted(w), _caller(call) {}
void User::searchFunctor::operator()(const SmartPtr<User>& spu) {
    UserInfo* uf = dynamic_cast<UserInfo*> (spu->account()->info());
    _wanted = utilities::Utils::toLowerCase(_wanted);
    switch(_s_type) {
        case 1:
            if(uf) {
                string fullName = utilities::Utils::toLowerCase(uf->name() + " " + uf->surname());
                if(utilities::Utils::toLowerCase(uf->name()) == _wanted || utilities::Utils::toLowerCase(uf->surname()) == _wanted || fullName == _wanted) {
                    _result.insert(std::pair<string, string>(spu->account()->username().login(), uf->name() + " " + uf->surname() + "\n"));
                    spu->addVisit();
                }
            }
        break;
        case 2:
            if(uf) {
                string fullName = utilities::Utils::toLowerCase(uf->name() + " " + uf->surname());
                if(utilities::Utils::toLowerCase(uf->name()) == _wanted || utilities::Utils::toLowerCase(uf->surname()) == _wanted || fullName == _wanted) {
                    _result.insert(std::pair<string, string>(spu->account()->username().login(), spu->account()->info()->printHtml() + "\n"));
                    spu->addVisit();
                }
            }
        break;
        case 3:
            if(!_wanted.empty() && _wanted.at(0) == ':') {
                if(uf) {
                    vector<string> skills = uf->skills();
                    vector<string>::iterator itr = skills.begin();
                    for(; itr < skills.end(); ++itr)
                        *itr = utilities::Utils::toLowerCase(*itr);
                    vector<string> input;
                    vector<string>::iterator it;
                    bool found = false;
                    _wanted.erase(_wanted.begin());
                    std::string token;
                    std::istringstream ss(_wanted);
                    while(std::getline(ss, token, ',')) {
                        token.erase(remove_if(token.begin(), token.end(), isspace), token.end());
                        input.push_back(token);
                    }
                    it = input.begin();
                    for(; it < input.end() && !found; ++it)
                        if((std::find(skills.begin(), skills.end(), *it) != skills.end()) && (spu->account()->username().login() != _caller->account()->username().login()))
                            found = false;
                        else found = true;
                    if(!found) {
                        _result.insert(std::pair<string, string>(spu->account()->username().login(), spu->account()->info()->printHtml() + "\n" + spu->net()->printHtml()));
                        spu->addVisit();
                    }
                }
            }
            else {
                if(uf) {
                    vector<string> skills = uf->skills();
                    vector<string>::iterator it = skills.begin();
                    for(; it < skills.end(); ++it)
                        *it = utilities::Utils::toLowerCase(*it);
                    string fullName = utilities::Utils::toLowerCase(uf->name() + " " + uf->surname());
                    if((utilities::Utils::toLowerCase(uf->name()) == _wanted ||
                       utilities::Utils::toLowerCase(uf->surname()) == _wanted ||
                       fullName == _wanted || std::find(skills.begin(), skills.end(), _wanted) != skills.end()) && (spu->account()->username().login() != _caller->account()->username().login())){
                        _result.insert(std::pair<string, string>(spu->account()->username().login(), spu->account()->info()->printHtml() + "\n" + spu->net()->printHtml()));
                        spu->addVisit();
                        if(spu->account()->prLevel() == executive) {
                            ExecutiveUser* eu = dynamic_cast<ExecutiveUser*> (&(*spu));
                            eu->addKeyword(_wanted);
                            eu->addVisitor(SmartPtr<User>(const_cast<User*> (_caller)));
                        }
                    }
                }
            }
        break;
        default:
            std::cout << "Schifo search" << std::endl;
        break;
    }
}
map<string, string> User::searchFunctor::result() const {
    return _result;
}
User::linkedWith::linkedWith(int s = 0, User* usr = 0) : _offset(s), _owner(usr) {}
void User::linkedWith::operator()(const SmartPtr<User>& spu) {
    if(!_owner->linked((spu->account()->username())) && (spu->account()->username()) != (_owner->account()->username()))
        if(_owner->similarity(spu) >= _offset)
            _mates.push_back(spu);
}
vector<SmartPtr<User> > User::linkedWith::result() const {
    return _mates;
}
vector<SmartPtr<User> > User::listPossibleLinks(const LinqDB& db) const {
    return std::for_each(db.begin(), db.end(), linkedWith(40, const_cast<User*> (this))).result();
}
void User::addContact(User* usr) {
    _net->addUser(usr);
}
void User::removeContact(const Username& usr) {
    _net->removeUser(usr);
}
Account* User::account() const {
    return _acc;
}
LinqNet* User::net() const {
    return _net;
}
int User::visitCount() const {
    return _visitcount;
}
void User::setVisitCount(int count) {
    _visitcount = count;
}
void User::addVisit() {
    _visitcount++;
}
int User::similarity(const SmartPtr<User>& user) const {
    UserInfo* uf = dynamic_cast<UserInfo*> (_acc->info());
    UserInfo* host = dynamic_cast<UserInfo*> (user->account()->info());
    double counter = 0;
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
    return static_cast<int> (counter);
}
int User::outMailCount() const {
    return _outMail.size();
}
bool User::linked(const Username& usr) const {
    bool found = false;
    vector<Username> v = net()->username();
    vector<Username>::const_iterator it = v.begin();
    for(; it < v.end() && !found; ++it)
        if((*it).login() == usr.login()) found = true;
    return found;
}
void User::loadInMail(const Message& mex) {
    _inMail.push_back(SmartPtr<Message> (const_cast<Message*> (&mex)));
}
list<SmartPtr<Message> > User::inMail() const {
    return _inMail;
}
list<SmartPtr<Message> > User::outMail() const {
    return _outMail;
}
void User::setInMail(const list<SmartPtr<Message> >& l) {
    _inMail = l;
}

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
void BasicUser::sendMessage(const Message& mex) {
    loadOutMail(mex);
}
void BasicUser::loadOutMail(const Message& mex) {
    if(_outMail.size() < basicMailLimit)
        _outMail.push_back(SmartPtr<Message> (const_cast<Message*> (&mex)));
}
unsigned int BasicUser::basicLimit() {
    return basicMailLimit;
}
unsigned int BasicUser::basicMailLimit = 10;

BusinessUser::BusinessUser(Account* ac) : BasicUser(ac) {}
BusinessUser::BusinessUser(const BusinessUser& usr) : BasicUser(usr)/*, _groups(usr._groups)*/ {
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
void BusinessUser::sendMessage(const Message& mex) {
    loadOutMail(mex);
}
void BusinessUser::loadOutMail(const Message& mex) {
    if(_outMail.size() < businessMailLimit)
        _outMail.push_back(SmartPtr<Message> (const_cast<Message*> (&mex)));
}
list<Group*> BusinessUser::groups() const {
    return _groups;
}
void BusinessUser::addGroup(const Group& g) {
    _groups.push_back(const_cast<Group*> (&g)); // controllo gruppi duplicati
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
// void BusinessUser::addPost(const Group& g, const Post& p) {
//     list<Group*>::iterator it = _groups.begin();
//     for(; it != _groups.end(); ++it)
//         if((**it) == g)
//             (*it)->insertPost(p);
// }
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
            // list<SmartPtr<User> > members = (*it)->members();
            bool found = false;
            if((**it) == *gr)
                ex->removeGroup(**it);
            // list<SmartPtr<User> >::iterator j = members.begin();
            // for(; j != members.end() && !found; ++j)
            //     if((*j)->username()->login() == us.login())
            //         found = true;
            // if(found) bu->removeGroup(*it)
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
void ExecutiveUser::sendMessage(const Message& mex) {
    loadOutMail(mex);
}
void ExecutiveUser::loadOutMail(const Message& mex) {
    _outMail.push_back(SmartPtr<Message> (const_cast<Message*> (&mex)));
}
void ExecutiveUser::addKeyword(const string& key) {
    ++_keywords[key];
}
void ExecutiveUser::globalRemoveGroup(const LinqDB& db, const Group& g) {
    std::for_each(db.begin(), db.end(), RemoveGroup(const_cast<Group*> (&g)));
    LinqDB& d = const_cast<LinqDB&> (db);
    d.deleteGroup(g);
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