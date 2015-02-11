#include "info.h"
#include "dispatcher.h"
#include "error.h"
#include <iostream>

Info::~Info() {}
UserInfo::UserInfo(const string& n, const string& s, const string& e, const string& a, const string& t, const string& w, const QDate& b) :
                _name(n), _surname(s), _email(e), _address(a), _telephon(t), _website(w){
                    if(b > QDate::currentDate()) throw Error(date, "Birthdate must be prior current date.");
                    else _birthdate = b;
                }
UserInfo::UserInfo(const UserInfo& uf) : _name(uf._name), _surname(uf._surname), _email(uf._email), _address(uf._address),
                _telephon(uf._telephon), _website(uf._website), _languages(uf._languages),
                _skills(uf._skills), _interests(uf._interests), _birthdate(uf._birthdate) {
                    for(list<Experience*>::const_iterator it = uf._exp.begin(); it != uf._exp.end(); ++it)
                        _exp.push_back(new Experience(**it));
                }
UserInfo& UserInfo::operator=(const UserInfo& uif) {
    if(this != &uif) {
        _name = uif._name;
        _surname = uif._surname;
        _birthdate = uif._birthdate;
        _address = uif._address;
        _email = uif._email;
        _telephon = uif._telephon;
        _website = uif._website;
        _languages = uif._languages;
        _interests = uif._interests;
        _skills = uif._skills;
        _exp = uif._exp;
    }
    return *this;
}
UserInfo::~UserInfo() {
    _skills.clear();
    _interests.clear();
    _languages.clear();
    for(list<Experience*>::const_iterator it = _exp.begin(); it != _exp.end(); ++it)
        delete *it;
    _exp.clear();
}
Info* UserInfo::clone() const {
    return new UserInfo(*this);
}
string UserInfo::name() const {
    return _name;
}
string UserInfo::surname() const {
    return _surname;
}
QDate UserInfo::birthdate() const {
    return _birthdate;
}
string UserInfo::email() const {
    return _email;
}
string UserInfo::address() const {
    return _address;
}
string UserInfo::telephon() const {
    return _telephon;
}
string UserInfo::website() const {
    return _website;
}
vector<string> UserInfo::languages() const {
    return _languages;
}
vector<string> UserInfo::skills() const {
    return _skills;
}
vector<string> UserInfo::interests() const {
    return _interests;
}
list<Experience*> UserInfo::experiences() const {
    return _exp;
}
void UserInfo::setName(const string& n) {
    _name = n;
}
void UserInfo::setSurname(const string& s) {
    _surname = s;
}
void UserInfo::setBirthdate(const QDate& b) throw(Error) {
    if(b > QDate::currentDate()) throw Error(date, "Birthdate must be prior current date");
    else _birthdate = b;
}
void UserInfo::setEmail(const string& e) {
    _email = e;
}
void UserInfo::setTelephon(const string& t) {
    _telephon = t;
}
void UserInfo::setAddress(const string& a) {
    _address = a;
}
void UserInfo::setWebsite(const string& site) {
    _website = site;
}
void UserInfo::addLanguage(const string& newlang) {
    vector<string>::iterator it = _languages.begin();
    bool isPresent = false;
    for(; it < _languages.end() && !isPresent; ++it)
        if(*it == newlang)
            isPresent = true;
    if(!isPresent) _languages.push_back(newlang);
}
void UserInfo::removeLanguage(const string& lang) {
    vector<string>::iterator it = _languages.begin();
    bool isPresent = false;
    for(; it < _languages.end() && !isPresent; ++it)
        if(*it == lang) {
            _languages.erase(it);
            isPresent = true;
        }
}
void UserInfo::addSkill(const string& newskill) {
    vector<string>::iterator it = _skills.begin();
    bool isPresent = false;
    for(; it < _skills.end() && !isPresent; ++it)
        if(*it == newskill)
            isPresent = true;
    if(!isPresent) _skills.push_back(newskill);
}
void UserInfo::removeSkill(const string& skill) {
    vector<string>::iterator it = _skills.begin();
    bool isPresent = false;
    for(; it < _skills.end() && !isPresent; ++it)
        if(*it == skill) {
            _skills.erase(it);
            isPresent = true;
        }
}
void UserInfo::addInterest(const string& newinterest) {
    vector<string>::iterator it = _interests.begin();
    bool isPresent = false;
    for(; it < _interests.end() && !isPresent; ++it)
        if(*it == newinterest)
            isPresent = true;
    if(!isPresent) _interests.push_back(newinterest);
}
void UserInfo::removeInterest(const string& inter) {
    vector<string>::iterator it = _interests.begin();
    bool isPresent = false;
    for(; it < _interests.end() && !isPresent; ++it)
        if(*it == inter) {
            _interests.erase(it);
            isPresent = true;
        }
}
void UserInfo::addExperience(const Experience& newxp) {
    _exp.push_back(const_cast<Experience*> (&newxp));
}
void UserInfo::removeExperience(const Experience& e) {
    bool found = false;
    for(list<Experience*>::iterator it = _exp.begin(); it != _exp.end() && !found; ++it)
        if(**it == e) {
            delete *it;
            _exp.erase(it);
            found = true;
        }
}
int UserInfo::age() const {
    QDate today = QDate::currentDate();
    int age = today.toJulianDay() - _birthdate.toJulianDay();
    if (age == 0) return -1;
    return age / 365;
}
string UserInfo::print() const {
    vector<string>::const_iterator it = _interests.begin();
    string ret = "";
    ret += _name + " , " + _surname + " , " + _address + " , " + _telephon + ", nato il " + _birthdate.toString().toStdString() + "\n";
    ret += "E-mail >> " + _email + " Sito web >> " + _website + "\n";
    ret += "Personal interests >> ";
    for(; it < _interests.end(); ++it)
        ret += *it + ", ";
    ret += "\nPersonal skills >> ";
    it = _skills.begin();
    for(; it < _skills.end(); ++it)
        ret += *it + ", ";
    ret += "\nFormation >> ";
    list<Experience*>::const_iterator itr = _exp.begin();
    for(; itr != _exp.end(); ++itr)
        ret += (*itr)->location() + ", " + (*itr)->from().toString().toStdString() + ", " + (*itr)->to().toString().toStdString() + " ";
    return ret;
}
string UserInfo::dispatch(const Dispatcher& d) const {
        return d.dispatch(*this);
}

Bio::Bio(const string& n, const string& s, const string& e, const string& a, const string& t, const string& w, const QDate& b, const string& bio) : UserInfo(n, s, e, a, t, w, b), _bio(bio) {}
Bio::Bio(const Bio& bio) : UserInfo(bio), _bio(bio._bio) {}
Bio::~Bio() {}
Info* Bio::clone() const {
    return new Bio(*this);
}
const string& Bio::bio() const {
    return _bio;
}
void Bio::setBio(const string& bio) {
    _bio = bio;
}
string Bio::print() const {
    return "";
}
string Bio::dispatch(const Dispatcher& d) const {
    return d.dispatch(*this);
}
