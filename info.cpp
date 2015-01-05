#include "info.h"

UserInfo::SmartExp::SmartExp(Experience* exp) : ptr(exp->clone()) {}
UserInfo::SmartExp::SmartExp(const SmartExp& sm_exp) : ptr((sm_exp.ptr)->clone()) {}
UserInfo::SmartExp& UserInfo::SmartExp::operator=(const SmartExp& sm_exp) {
    if(this != &sm_exp) {
        delete ptr;
        ptr = (sm_exp.ptr)->clone();
    }
    return *this;
}
UserInfo::SmartExp::~SmartExp() { delete ptr; }
Experience& UserInfo::SmartExp::operator*() const {
    return *ptr;
}
Experience* UserInfo::SmartExp::operator->() const {
    return ptr;
}

Info::~Info() {}
UserInfo::UserInfo() {}
UserInfo::UserInfo(bool sx, string n, string s, string b, string e, string a, string t, string w) :
                _sex(sx), _name(n), _surname(s), _birthdate(b), _email(e), _address(a), _telephon(t), _website(w){}
UserInfo::UserInfo(const UserInfo& uf) :
                _sex(uf._sex), _name(uf._name), _surname(uf._surname),_birthdate(uf._birthdate),
                _email(uf._email), _address(uf._address), _telephon(uf._telephon), _skills(uf._skills),
                _exps(uf._exps), _formations(uf._formations), _interests(uf._interests), _website(uf._website), _languages(uf._languages) {}
UserInfo& UserInfo::operator=(const UserInfo& uif) {
    if(this != &uif) {
        _name = uif._name;
        _surname = uif._surname;
        _birthdate = uif._birthdate;
        _address = uif._address;
        _email = uif._email;
        _telephon = uif._telephon;
        _sex = uif._sex;
    }
    return *this;
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
string UserInfo::birthdate() const {
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
bool UserInfo::sex() const {
    return _sex;
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
vector<SmartPtr<Experience> > UserInfo::experience() const {
    return _exps;
}
vector<SmartPtr<Experience> > UserInfo::formations() const {
    return _formations;
}
void UserInfo::setName(string n = "") {
    _name = n;
}
void UserInfo::setSurname(string s = "") {
    _surname = s;
}
void UserInfo::setBirthdate(string b = "") {
    _birthdate = b;
}
void UserInfo::setEmail(string e = "") {
    _email = e;
}
void UserInfo::setTelephon(string t = "") {
    _telephon = t;
}
void UserInfo::setAddress(string a = "") {
    _address = a;
}
void UserInfo::setSex(bool s = true) {
    _sex = s;
}
void UserInfo::setWebsite(string site = "") {
    _website = site;
}
void UserInfo::addLanguage(string newlang) {
    vector<string>::iterator it = _languages.begin();
    bool isPresent = false;
    for(; it < _languages.end() && !isPresent; ++it)
        if(*it == newlang)
            isPresent = true;
    if(!isPresent) _languages.push_back(newlang);
}
void UserInfo::addSkill(string newskill) {
    vector<string>::iterator it = _skills.begin();
    bool isPresent = false;
    for(; it < _skills.end() && !isPresent; ++it)
        if(*it == newskill)
            isPresent = true;
    if(!isPresent) _skills.push_back(newskill);
}
void UserInfo::addInterest(string newinterest = "") {
    vector<string>::iterator it = _interests.begin();
    bool isPresent = false;
    for(; it < _interests.end() && !isPresent; ++it)
        if(*it == newinterest)
            isPresent = true;
    if(!isPresent) _interests.push_back(newinterest);
}
void UserInfo::addExperience(Experience* newxp) {
    _exps.push_back(SmartPtr<Experience>(newxp));
}
void UserInfo::addFormation(Experience* newfrm) {
    _formations.push_back(SmartPtr<Experience>(newfrm));
}
int UserInfo::age() const {
    return 26;
}
string UserInfo::print() const {
    vector<string>::const_iterator it = _interests.begin();
    string ret = "";
    string sex = "";
    if(this->sex()) sex = "Maschio";
    else sex = "Femmina";
    ret += _name + " , " + _surname + " , " + sex + " , " + _address + " , " + _telephon + ", nato il " + _birthdate + "\n";
    ret += "E-mail >> " + _email + " Sito web >> " + _website + "\n";
    ret += "Personal interests >> ";
    for(; it < _interests.end(); ++it)
        ret += *it + ", ";
    ret += "\nPersonal skills >> ";
    it = _skills.begin();
    for(; it < _skills.end(); ++it)
        ret += *it + ", ";
    ret += "\nFormation >> ";
    vector<SmartPtr<Experience> >::const_iterator itr = _formations.begin();
    Instruction* tmp;
    for(; itr < _formations.end(); ++itr) {
        tmp = dynamic_cast<Instruction*> (&(**itr));
        if(tmp) ret += tmp->location() + ", " + tmp->from() + ", " + tmp->to() + " ";
    }
    return ret;
}
string UserInfo::printHtml() const {
    string html = "";
    html = "<h2>" + _name + " " + _surname + "</h2>";
    html += "<p style='font-weight: 400; font-size:13px;'>Student  &nbsp;26 years old<br>";
    html += _address + "&nbsp;&nbsp;" + _telephon + "</p>";
    html += "<h4>Interests</h4><p style='font-weight: 400; font-size:13px;'>";
    vector<string>::const_iterator it;
    if(!_interests.empty()) {
        it = _interests.begin();
        for(; it < _interests.end(); ++it)
            html += *it + " ";
        html += "</p>";
    }
    if(!_skills.empty()) {
        html += "<h4><img src='img/profile11.png'>  Skills</h4><p style='font-weight: 400; font-size:13px;'>";
        it = _skills.begin();
        for(; it < _skills.end(); ++it)
            html += "<span style='background-color:rgba(102,102,102,.5);'>&nbsp;"  + *it + "&nbsp;</span>&nbsp;&nbsp;";
        html += "</p>";
    }
    if(!_languages.empty()) {
        html += "<h4>Languages</h4><p style='font-weight: 400; font-size:13px;'>";
        it = _languages.begin();
        for(; it < _languages.end(); ++it)
            html += *it + " ";
        html += "</p>";
    }
    if(!_formations.empty()) {
        html += "<h4>Educations</h4><p style='font-weight: 400; font-size:13px;'>";
        vector<SmartPtr<Experience> >::const_iterator itr = _formations.begin();
        Instruction* tmp;
        for(; itr < _formations.end(); ++itr) {
            tmp = dynamic_cast<Instruction*> (&(**itr));
            if(tmp)
                if(itr == _formations.end() - 1)
                    html += tmp->location() + " from " + tmp->from() + " to " + tmp->to();
                else
                    html += tmp->location() + " from " + tmp->from() + " to " + tmp->to() + "<br>";
        }
    }
    html += "<h4>Contacts</h4><p style='font-weight: 400; font-size:13px'>" + _email + " &nbsp;&nbsp;<a style='color:#4782EC;' href='#'>" + _website + "</a></p>";
    html += "<h4>Bio</h4>";
    return html;
}