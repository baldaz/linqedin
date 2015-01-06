#include "user.h"
#include "linqnet.h"
#include "linqdb.h"

using std::vector;

User::User() : _acc(new Account()), _net(new LinqNet()) {}
User::User(Account* ac, LinqNet* lq) : _acc(ac), _net(lq) {}
User::User(const User& usr) : _acc(usr._acc), _net(usr._net) /*: _acc(usr._acc->clone()), _net(usr._net->clone())*/ {}
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
    // std::cout << "trovato user" << std::endl;
}
Account* User::account() const {
    return _acc;
}
LinqNet* User::net() const {
    return _net;
}

User::searchFunctor::searchFunctor(int s = 0, string w = "") : _s_type(s), _wanted(w) {}
void User::searchFunctor::operator()(const SmartPtr<User>& spu) {
    UserInfo* uf = NULL;
    switch(_s_type) {
        case 1:
            uf = dynamic_cast<UserInfo*> (spu->account()->info());
            if(uf) {
                string fullName = uf->name() + " " + uf->surname();
                if(uf->name() == _wanted || uf->surname() == _wanted || fullName == _wanted)
                    _result += uf->name() + " " + uf->surname() + "\n";
            }
        break;
        case 2:
            uf = dynamic_cast<UserInfo*> (spu->account()->info());
            if(uf) {
                string fullName = uf->name() + " " + uf->surname();
                if(uf->name() == _wanted || uf->surname() == _wanted || fullName == _wanted)
                    _result += spu->account()->info()->printHtml() + "\n";
            }
        break;
        case 3:
            uf = dynamic_cast<UserInfo*> (spu->account()->info());
            if(uf) {
                string fullName = uf->name() + " " + uf->surname();
                if(uf->name() == _wanted || uf->surname() == _wanted || fullName == _wanted) {
                    _result += spu->account()->info()->printHtml() + "\n";
                    _result += spu->net()->printHtml();
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
BasicUser::BasicUser(Account* ac, LinqNet* lq) : User(ac, lq) {}
BasicUser::BasicUser(const BasicUser& usr) : User(usr) {}
User* BasicUser::clone() const {
    return new BasicUser(*this);
}
string BasicUser::userSearch(const LinqDB& db, string wanted) const {
    return std::for_each(db.begin(), db.end(), searchFunctor(1, wanted)).result();
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

ExecutiveUser::ExecutiveUser() : BusinessUser() {}
ExecutiveUser::ExecutiveUser(Account* ac, LinqNet* lq) : BusinessUser(ac, lq) {}
ExecutiveUser::ExecutiveUser(const ExecutiveUser& usr) : BusinessUser(usr) {}
User* ExecutiveUser::clone() const {
    return new ExecutiveUser(*this);
}
string ExecutiveUser::userSearch(const LinqDB& db, string wanted) const {
    return std::for_each(db.begin(), db.end(), searchFunctor(3, wanted)).result();
}