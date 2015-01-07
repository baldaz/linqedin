#include "user.h"
#include "linqnet.h"
#include "linqdb.h"
#include "utils.h"

using std::vector;

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
void User::addContact(User* usr) {
    _net->addUser(usr);
}
void User::removeContact(Username* usr) {
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

User::searchFunctor::searchFunctor(int s = 0, string w = "") : _s_type(s), _wanted(w) {}
void User::searchFunctor::operator()(const SmartPtr<User>& spu) {
    UserInfo* uf = NULL;
    _wanted = utilities::Utils::toLowerCase(_wanted);
    switch(_s_type) {
        case 1:
            uf = dynamic_cast<UserInfo*> (spu->account()->info());
            if(uf) {
                string fullName = utilities::Utils::toLowerCase(uf->name() + " " + uf->surname());
                if(utilities::Utils::toLowerCase(uf->name()) == _wanted || utilities::Utils::toLowerCase(uf->surname()) == _wanted || fullName == _wanted) {
                    _result += uf->name() + " " + uf->surname() + "\n";
                    spu->addVisit();
                }
            }
        break;
        case 2:
            uf = dynamic_cast<UserInfo*> (spu->account()->info());
            if(uf) {
                string fullName = utilities::Utils::toLowerCase(uf->name() + " " + uf->surname());
                if(utilities::Utils::toLowerCase(uf->name()) == _wanted || utilities::Utils::toLowerCase(uf->surname()) == _wanted || fullName == _wanted) {
                    _result += spu->account()->info()->printHtml() + "\n";
                    _result += "<hr>";
                    spu->addVisit();
                }
            }
        break;
        case 3:
            uf = dynamic_cast<UserInfo*> (spu->account()->info());
            if(uf) {
                vector<string> skills = uf->skills();
                vector<string>::iterator it = skills.begin();
                for(; it < skills.end(); ++it)
                    *it = utilities::Utils::toLowerCase(*it);
                string fullName = utilities::Utils::toLowerCase(uf->name() + " " + uf->surname());
                if(utilities::Utils::toLowerCase(uf->name()) == _wanted ||
                   utilities::Utils::toLowerCase(uf->surname()) == _wanted ||
                   fullName == _wanted || utilities::Utils::contains(skills, _wanted)) {
                    _result += spu->account()->info()->printHtml() + "\n";
                    _result += spu->net()->printHtml();
                    _result += "<hr>";
                    spu->addVisit();
                }
            }
        break;
        default:
            std::cout << "Schifo search" << std::endl;
        break;
    }
}
string User::searchFunctor::result() const {
    return _result;
}

BasicUser::BasicUser() : User() {}
BasicUser::BasicUser(Account* ac, LinqNet* lq) : User(ac, lq){}
BasicUser::BasicUser(const BasicUser& usr) : User(usr){}
User* BasicUser::clone() const {
    return new BasicUser(*this);
}
string BasicUser::userSearch(const LinqDB& db, string wanted) const {
    return std::for_each(db.begin(), db.end(), searchFunctor(1, wanted)).result();
}

BusinessUser::linkedWith::linkedWith(int s = 0, LinqNet* net = 0) : _links(s), _network(net) {}
void BusinessUser::linkedWith::operator()(const SmartPtr<User>& spu) {

}
vector<SmartPtr<User> > BusinessUser::linkedWith::result() const {
    return _mates;
}
BusinessUser::BusinessUser() : BasicUser() {}
BusinessUser::BusinessUser(Account* ac, LinqNet* lq) : BasicUser(ac, lq) {}
BusinessUser::BusinessUser(const BusinessUser& usr) : BasicUser(usr) {}
User* BusinessUser::clone() const {
    return new BusinessUser(*this);
}
string BusinessUser::userSearch(const LinqDB& db, string wanted) const {
    return std::for_each(db.begin(), db.end(), searchFunctor(2, wanted)).result();
}
vector<SmartPtr<User> > BusinessUser::listPossibleLinks(const LinqDB& db) const {
    return std::for_each(db.begin(), db.end(), linkedWith(3, this->net())).result();
}

ExecutiveUser::ExecutiveUser() : BusinessUser() {}
ExecutiveUser::ExecutiveUser(Account* ac, LinqNet* lq) : BusinessUser(ac, lq) {}
ExecutiveUser::ExecutiveUser(const ExecutiveUser& usr) : BusinessUser(usr) {}
User* ExecutiveUser::clone() const {
    return new ExecutiveUser(*this);
}
string ExecutiveUser::userSearch(const LinqDB& db, string wanted) const {
    return std::for_each(db.begin(), db.end(), searchFunctor(3, wanted)).result();
}