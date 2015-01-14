#include "user.h"
#include "linqnet.h"
#include "linqdb.h"
#include "utils.h"
#include <sstream>

using std::vector;
using std::map;

User::User() : _acc(new Account()), _net(new LinqNet()), _visitcount(0)  {}
User::User(Account* ac, LinqNet* lq) : _acc(ac), _net(lq), _visitcount(0)  {}
User::User(const User& usr) : _acc(usr._acc), _net(usr._net), _visitcount(usr._visitcount) /*: _acc(usr._acc->clone()), _net(usr._net->clone())*/ {}
User::~User() { }
User& User::operator=(const User& usr) {
    if(this != &usr) {
        delete _acc;
        delete _net;
        _acc = usr._acc;
        _net = usr._net;
    }
    return *this;
}

User::searchFunctor::searchFunctor(int s = 0, const string& w = "", const User* call = 0) : _s_type(s), _wanted(w), _caller(call) {}
void User::searchFunctor::operator()(const SmartPtr<User>& spu) {
    UserInfo* uf = NULL;
    _wanted = utilities::Utils::toLowerCase(_wanted);
    switch(_s_type) {
        case 1:
            uf = dynamic_cast<UserInfo*> (spu->account()->info());
            if(uf) {
                string fullName = utilities::Utils::toLowerCase(uf->name() + " " + uf->surname());
                if(utilities::Utils::toLowerCase(uf->name()) == _wanted || utilities::Utils::toLowerCase(uf->surname()) == _wanted || fullName == _wanted) {
                    // _result.push_back(uf->name() + " " + uf->surname() + "\n");
                    _result.insert(std::pair<string, string>(spu->account()->username()->login(), uf->name() + " " + uf->surname() + "\n"));
                    spu->addVisit();
                }
            }
        break;
        case 2:
            uf = dynamic_cast<UserInfo*> (spu->account()->info());
            if(uf) {
                string fullName = utilities::Utils::toLowerCase(uf->name() + " " + uf->surname());
                if(utilities::Utils::toLowerCase(uf->name()) == _wanted || utilities::Utils::toLowerCase(uf->surname()) == _wanted || fullName == _wanted) {
                    // _result.push_back(spu->account()->info()->printHtml() + "\n");
                    _result.insert(std::pair<string, string>(spu->account()->username()->login(), spu->account()->info()->printHtml() + "\n"));
                    spu->addVisit();
                }
            }
        break;
        case 3:
            uf = dynamic_cast<UserInfo*> (spu->account()->info());
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
                        if((std::find(skills.begin(), skills.end(), *it) != skills.end()) && (spu->account()->username()->login() != _caller->account()->username()->login()))
                            found = false;
                        else found = true;
                    if(!found) {
                        _result.insert(std::pair<string, string>(spu->account()->username()->login(), spu->account()->info()->printHtml() + "\n" + spu->net()->printHtml()));
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
                       fullName == _wanted || std::find(skills.begin(), skills.end(), _wanted) != skills.end()) && (spu->account()->username()->login() != _caller->account()->username()->login())){
                        // _result.push_back(spu->account()->info()->printHtml() + "\n" + spu->net()->printHtml());
                        _result.insert(std::pair<string, string>(spu->account()->username()->login(), spu->account()->info()->printHtml() + "\n" + spu->net()->printHtml()));
                        spu->addVisit();
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

void BasicUser::addContact(User* usr) {
    _net->addUser(usr);
}
void BasicUser::removeContact(const Username& usr) {
    _net->removeUser(usr);
}
Account* BasicUser::account() const {
    return _acc;
}
LinqNet* BasicUser::net() const {
    return _net;
}
int BasicUser::visitCount() const {
    return _visitcount;
}
void BasicUser::setVisitCount(int count) {
    _visitcount = count;
}
void BasicUser::addVisit() {
    _visitcount++;
}
int BasicUser::similarity(User* user) const {
    UserInfo* uf = dynamic_cast<UserInfo*> (this->account()->info());
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
bool BasicUser::linked(const Username& usr) const {
    bool found = false;
    vector<SmartPtr<Username> > v = net()->username();
    vector<SmartPtr<Username> >::const_iterator it = v.begin();
    for(; it < v.end() && !found; ++it)
        if((*it)->login() == usr.login()) found = true;
    return found;
}

BasicUser::BasicUser() : User() {}
BasicUser::BasicUser(Account* ac, LinqNet* lq) : User(ac, lq){}
BasicUser::BasicUser(const BasicUser& usr) : User(usr){}
User* BasicUser::clone() const {
    return new BasicUser(*this);
}
map<string, string> BasicUser::userSearch(const LinqDB& db, const string& wanted) const {
    return std::for_each(db.begin(), db.end(), searchFunctor(1, wanted, this)).result();
}

BasicUser::linkedWith::linkedWith(int s = 0, User* usr = 0) : _offset(s), _owner(usr) {}
void BasicUser::linkedWith::operator()(const SmartPtr<User>& spu) {
    if(!_owner->linked(*(spu->account()->username())) && *(spu->account()->username()) != *(_owner->account()->username()))
        if(_owner->similarity(&(*spu)) >= _offset)
            _mates.push_back(spu);
}
vector<SmartPtr<User> > BasicUser::linkedWith::result() const {
    return _mates;
}
vector<SmartPtr<User> > BasicUser::listPossibleLinks(const LinqDB& db) const {
    return std::for_each(db.begin(), db.end(), linkedWith(40, const_cast<BasicUser*> (this))).result();
}

BusinessUser::BusinessUser() : BasicUser() {}
BusinessUser::BusinessUser(Account* ac, LinqNet* lq) : BasicUser(ac, lq) {}
BusinessUser::BusinessUser(const BusinessUser& usr) : BasicUser(usr) {}
User* BusinessUser::clone() const {
    return new BusinessUser(*this);
}
map<string, string> BusinessUser::userSearch(const LinqDB& db, const string& wanted) const {
    return std::for_each(db.begin(), db.end(), searchFunctor(2, wanted, this)).result();
}

ExecutiveUser::ExecutiveUser() : BusinessUser() {}
ExecutiveUser::ExecutiveUser(Account* ac, LinqNet* lq) : BusinessUser(ac, lq) {}
ExecutiveUser::ExecutiveUser(const ExecutiveUser& usr) : BusinessUser(usr) {}
User* ExecutiveUser::clone() const {
    return new ExecutiveUser(*this);
}
map<string, string> ExecutiveUser::userSearch(const LinqDB& db, const string& wanted) const {
    return std::for_each(db.begin(), db.end(), searchFunctor(3, wanted, this)).result();
}
