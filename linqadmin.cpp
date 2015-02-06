#include "linqadmin.h"
#include "utils.h"
#include <sstream>

LinqAdmin::completeRemove::completeRemove(const Username& usr) : rmusr(usr) {}
LinqAdmin::completeRemove::~completeRemove() { }
void LinqAdmin::completeRemove::operator()(const SmartPtr<User>& user) const {
    user->removeContact(rmusr);
}

LinqAdmin::adminSearch::adminSearch(const string& w) : _wanted(w){}
void LinqAdmin::adminSearch::operator()(const SmartPtr<User>& user) {
    UserInfo* uf = dynamic_cast<UserInfo*> (user->account()->info());
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
                if(std::find(skills.begin(), skills.end(), *it) != skills.end())
                    found = false;
                else found = true;
            if(!found) _result.insert(std::pair<string, string>(user->account()->username().login(), user->showInfo() + "\n" + user->net()->printHtml()));
        }
    }
    else {
        if(uf) {
            vector<string> skills = uf->skills();
            vector<string>::iterator it = skills.begin();
            for(; it < skills.end(); ++it)
                *it = utilities::Utils::toLowerCase(*it);
            string fullName = utilities::Utils::toLowerCase(uf->name() + " " + uf->surname());
            if((utilities::Utils::toLowerCase(uf->name()) == _wanted || utilities::Utils::toLowerCase(uf->surname()) == _wanted || fullName == _wanted || std::find(skills.begin(), skills.end(), _wanted) != skills.end()))
                 _result.insert(std::pair<string, string>(user->account()->username().login(), user->showInfo() + "\n" + user->net()->printHtml()));
        }
    }
}
map<string,string> LinqAdmin::adminSearch::result() const {
    return _result;
}

LinqAdmin::LinqAdmin() : _db(new LinqDB()) {}
LinqAdmin::~LinqAdmin() { delete _db; }
void LinqAdmin::insertUser(User* newuser) {
    _db->addUser(newuser);
    save();
}
list<SmartPtr<User> > LinqAdmin::listUsers() const {
    return _db->db();
}
void LinqAdmin::insertUser(const string& username, const string& password, const map<string, string>& info) {
    string name = (info.find("name"))->second;
    string surname = info.find("surname")->second;
    string address = info.find("address")->second;
    string phone = info.find("telephone")->second;
    string website = info.find("website")->second;
    string email = info.find("e-mail")->second;
    string birthdate = info.find("birthdate")->second;
    string bio = info.find("bio")->second;
    Bio b(name, surname, email, address, phone, website, QDate::fromString(QString::fromStdString(birthdate), "dd.MM.yyyy"), bio);
    Username u(username, password);
    Subscription s(basic);
    CreditCard cd("N/A", "N/A");
    Payment p(&u, &s, &cd, true);
    Account a(&b, u, basic);
    a.addPayment(p);
    BasicUser nu(&a);
    this->insertUser(&nu);
}
void LinqAdmin::removeUser(const Username& user) {
    std::for_each(_db->begin(), _db->end(), completeRemove(user));
    _db->removeUser(user);
    save();
}
void LinqAdmin::alterSubscription(const Username& usr, privLevel newlevel) {
    User* current = _db->find(usr);
    current->account()->setPrLevel(newlevel);
    save();
}
map<string,string> LinqAdmin::find(const string& s) const {
    return std::for_each(_db->begin(), _db->end(), adminSearch(s)).result();
}
void LinqAdmin::save() const {
    _db->save();
}