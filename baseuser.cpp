#include "baseuser.h"
#include "linqnet.h"
#include "utils.h"
#include "dispatcher.h"
#include "linqdb.h"
#include <sstream>
#include <algorithm>

User::User(Account* ac) : _acc(ac->clone()), _net(new LinqNet()), _visitcount(0) {}
User::User(const User& usr) : _acc(usr._acc->clone()), _net(usr._net->clone()), _visitcount(usr._visitcount), _outMail(usr._outMail), _inMail(usr._inMail) {}
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
                    if(_result.size() < 50) {
                        _result.insert(std::pair<string, string>(spu->account()->username().login(), uf->name() + " " + uf->surname() + "\n"));
                        spu->addVisit();
                    }
                }
            }
        break;
        case 2:
            if(uf) {
                string fullName = utilities::Utils::toLowerCase(uf->name() + " " + uf->surname());
                if(utilities::Utils::toLowerCase(uf->name()) == _wanted || utilities::Utils::toLowerCase(uf->surname()) == _wanted || fullName == _wanted) {
                    if(_result.size() < 100) {
                        _result.insert(std::pair<string, string>(spu->account()->username().login(), spu->showInfo() + "\n"));
                        spu->addVisit();
                    }
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
                        if(_result.size() < 400) {
                            _result.insert(std::pair<string, string>(spu->account()->username().login(), spu->showInfo() + "\n" + spu->net()->printHtml()));
                            spu->addVisit();
                        }
                    }
                }
            }
            else {
                std::list<Group*> lg;
                if(BusinessUser* bs = dynamic_cast<BusinessUser*> (&(*spu)))
                    lg = bs->groups();
                std::vector<string> g_names;
                if(!lg.empty()) {
                    for(std::list<Group*>::iterator g = lg.begin(); g != lg.end(); ++g)
                        g_names.push_back(utilities::Utils::toLowerCase((*g)->name()));
                }
                if(uf) {
                    vector<string> skills = uf->skills();
                    vector<string>::iterator it = skills.begin();
                    for(; it < skills.end(); ++it)
                        *it = utilities::Utils::toLowerCase(*it);
                    string fullName = utilities::Utils::toLowerCase(uf->name() + " " + uf->surname());
                    if((utilities::Utils::toLowerCase(uf->name()) == _wanted ||
                        utilities::Utils::toLowerCase(uf->surname()) == _wanted ||
                        fullName == _wanted || std::find(skills.begin(), skills.end(), _wanted) != skills.end() ||
                        std::find(g_names.begin(), g_names.end(), _wanted) != g_names.end()) && (spu->account()->username().login() != _caller->account()->username().login())){
                        if(_result.size() < 400) {
                            _result.insert(std::pair<string, string>((spu)->account()->username().login(), (spu)->showInfo() + "\n" + (spu)->net()->printHtml()));
                            (spu)->addVisit();
                            if((spu)->account()->prLevel() == executive) {
                                ExecutiveUser* eu = dynamic_cast<ExecutiveUser*> (&(*(spu)));
                                eu->addKeyword(_wanted);
                                eu->addVisitor(SmartPtr<User>(const_cast<User*> (_caller)));
                            }
                        }
                    }
                }
            }
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
    return std::for_each(db.begin(), db.end(), linkedWith(45, const_cast<User*> (this))).result();
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
string User::showInfo() const {
    DispatcherHtml d;
    return _acc->info()->dispatch(d);
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
void User::loadOutMail(const Message& mex) {
    _outMail.push_back(SmartPtr<Message> (const_cast<Message*> (&mex)));
}
void User::deleteMessage(const Message& m) throw(Error) {
    bool found = false;
    for(list<SmartPtr<Message> >::iterator it = _inMail.begin(); it != _inMail.end() && !found; ++it)
        if(**it == m) {
            _inMail.erase(it);
            found = true;
        }
    if(!found) throw Error(mail, "Message not found");
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