#include "user.h"
#include "linqnet.h"
#include "linqdb.h"
#include "utils.h"
#include <sstream>

using std::vector;
using std::map;

User::User(Account* ac) : _acc(ac->clone()), _net(new LinqNet()), _visitcount(0)  {}
User::User(const User& usr) : _acc(usr._acc->clone()), _net(usr._net->clone()), _visitcount(usr._visitcount) {
    for(list<Message*>::const_iterator it = usr._inMail.begin(); it != usr._inMail.end(); ++it)
        _inMail.push_back(new Message(**it));
    for(list<Message*>::const_iterator it = usr._outMail.begin(); it != usr._outMail.end(); ++it)
        _outMail.push_back(new Message(**it));
}
User::~User() {
    delete _acc;
    delete _net;
    for(list<Message*>::iterator it = _inMail.begin(); it != _inMail.end(); ++it)
        delete *it;
    _inMail.clear();
    for(list<Message*>::iterator it = _outMail.begin(); it != _outMail.end(); ++it)
        delete *it;
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
    // Account acc = spu->account();
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
    // Account useracc = user->account();
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
bool User::linked(const Username& usr) const {
    bool found = false;
    vector<Username> v = net()->username();
    vector<Username>::const_iterator it = v.begin();
    for(; it < v.end() && !found; ++it)
        if((*it).login() == usr.login()) found = true;
    return found;
}
void User::loadInMail(const Message& mex) {
    _inMail.push_back(const_cast<Message*> (&mex));
}
list<Message*> User::inMail() const {
    return _inMail;
}
list<Message*> User::outMail() const {
    return _outMail;
}

BasicUser::BasicUser(Account* ac) : User(ac){}
BasicUser::BasicUser(const BasicUser& usr) : User(usr){}
User* BasicUser::clone() const {
    return new BasicUser(*this);
}
map<string, string> BasicUser::userSearch(const LinqDB& db, const string& wanted) const {
    return std::for_each(db.begin(), db.end(), searchFunctor(1, wanted, this)).result();
}
void BasicUser::sendMessage(const Username& dest, const string& obj, const string& body, bool read) {
    if(_outMail.size() < basicMailLimit) {
        Message mex((this->account()->username()), dest, obj, body, read);
        _outMail.push_back(&mex);
    }
}
void BasicUser::loadOutMail(const Message& mex) {
    if(_outMail.size() < basicMailLimit)
        _outMail.push_back(const_cast<Message*> (&mex));
}
unsigned int BasicUser::basicMailLimit = 10;

BusinessUser::BusinessUser(Account* ac) : BasicUser(ac) {}
BusinessUser::BusinessUser(const BusinessUser& usr) : BasicUser(usr) {}
User* BusinessUser::clone() const {
    return new BusinessUser(*this);
}
map<string, string> BusinessUser::userSearch(const LinqDB& db, const string& wanted) const {
    return std::for_each(db.begin(), db.end(), searchFunctor(2, wanted, this)).result();
}
void BusinessUser::sendMessage(const Username& dest, const string& obj, const string& body, bool read) {
    if(_outMail.size() < businessMailLimit) {
        Message mex((this->account()->username()), dest, obj, body, read);
        _outMail.push_back(&mex);
    }
}
void BusinessUser::loadOutMail(const Message& mex) {
    if(_outMail.size() < businessMailLimit)
        _outMail.push_back(const_cast<Message*> (&mex));
}
unsigned int BusinessUser::businessMailLimit = 25;

ExecutiveUser::ExecutiveUser(Account* ac) : BusinessUser(ac) {}
ExecutiveUser::ExecutiveUser(const ExecutiveUser& usr) : BusinessUser(usr), _keywords(usr._keywords) {}
ExecutiveUser::~ExecutiveUser() {_keywords.clear();}
User* ExecutiveUser::clone() const {
    return new ExecutiveUser(*this);
}
map<string, string> ExecutiveUser::userSearch(const LinqDB& db, const string& wanted) const {
    return std::for_each(db.begin(), db.end(), searchFunctor(3, wanted, this)).result();
}
void ExecutiveUser::sendMessage(const Username& dest, const string& obj, const string& body, bool read) {
    Message mex((this->account()->username()), dest, obj, body, read);
    _outMail.push_back(&mex);
}
void ExecutiveUser::loadOutMail(const Message& mex) {
    _outMail.push_back(const_cast<Message*> (&mex));
}
void ExecutiveUser::addKeyword(const string& key) {
    ++_keywords[key];
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