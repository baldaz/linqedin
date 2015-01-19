#include "info.h"

Info::~Info() {}
UserInfo::UserInfo() {}
UserInfo::UserInfo(bool sx, const string& n, const string& s, const string& b, const string& e, const string& a, const string& t, const string& w) :
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
UserInfo::~UserInfo() {
    _skills.clear();
    _interests.clear();
    _languages.clear();
    _formations.clear();
    _exps.clear();
}
Info* UserInfo::clone() const {
    return new UserInfo(*this);
}
const string& UserInfo::name() const {
    return _name;
}
const string& UserInfo::surname() const {
    return _surname;
}
const string& UserInfo::birthdate() const {
    return _birthdate;
}
const string& UserInfo::email() const {
    return _email;
}
const string& UserInfo::address() const {
    return _address;
}
const string& UserInfo::telephon() const {
    return _telephon;
}
bool UserInfo::sex() const {
    return _sex;
}
const string& UserInfo::website() const {
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
void UserInfo::setName(const string& n = "") {
    _name = n;
}
void UserInfo::setSurname(const string& s = "") {
    _surname = s;
}
void UserInfo::setBirthdate(const string& b = "") {
    _birthdate = b;
}
void UserInfo::setEmail(const string& e = "") {
    _email = e;
}
void UserInfo::setTelephon(const string& t = "") {
    _telephon = t;
}
void UserInfo::setAddress(const string& a = "") {
    _address = a;
}
void UserInfo::setSex(bool s = true) {
    _sex = s;
}
void UserInfo::setWebsite(const string& site = "") {
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
void UserInfo::addSkill(const string& newskill) {
    vector<string>::iterator it = _skills.begin();
    bool isPresent = false;
    for(; it < _skills.end() && !isPresent; ++it)
        if(*it == newskill)
            isPresent = true;
    if(!isPresent) _skills.push_back(newskill);
}
void UserInfo::addInterest(const string& newinterest = "") {
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
    html = "<html><body>";
    html += "<h2>" + _name + " " + _surname + "</h2>";
    html += "<p style='font-weight: 400; font-size:14px;'>Student 26 years old<br>";
    html += _address + "</p>";
    html += "<h4><img src='img/rugby100.png'>  Interests</h4><p style='font-weight: 400; font-size:14px;'>";
    vector<string>::const_iterator it;
    if(!_interests.empty()) {
        it = _interests.begin();
        for(; it < _interests.end(); ++it)
            html += *it + " ";
        html += "</p>";
    }
    if(!_skills.empty()) {
        html += "<h4><img src='img/atom2.png'>  Skills</h4><p style='font-weight: 400; font-size:14px; line-height:26px;'>";
        it = _skills.begin();
        for(; it < _skills.end(); ++it)
            html += "<span style='background-color:rgba(102,102,102,.5);'>&nbsp;"  + *it + "&nbsp;</span>&nbsp;&nbsp;";
        html += "</p>";
    }
    if(!_languages.empty()) {
        html += "<h4><img src='img/flag27.png'>  Languages</h4><p style='font-weight: 400; font-size:14px;'>";
        it = _languages.begin();
        for(; it < _languages.end(); ++it)
            html += *it + " ";
        html += "</p>";
    }
    if(!_formations.empty()) {
        html += "<h4><img src='img/graduate34.png'>  Educations</h4><p style='font-weight: 400; font-size:14px;'>";
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
    html += "</p>";
    html += "<h4><img src='img/business133.png'>  Contacts</h4><p style='font-weight: 400; font-size:14px'>" + _email + " &nbsp;&nbsp;<a style='color:#4782EC;' href='#'>" + _website + "</a><br> Telephon  " + _telephon + "</p>";
    html += "<h4>Bio</h4></body></html>";
    return html;
}

Bio::Bio(bool sx, const string& n, const string& s, const string& b, const string& e, const string& a, const string& t, const string& w, const string& bio = "") : UserInfo(sx, n, s, b, e, a, t, w), _bio(bio) {}
Bio::Bio(const Bio& bio) :
    UserInfo(bio._sex, bio._name, bio._surname, bio._birthdate, bio._email, bio._address, bio._telephon, bio._website), _bio(bio._bio) {}
Bio::~Bio() {}
Info* Bio::clone() const {
    return new Bio(*this);
}
const string& Bio::bio() const {
    return _bio;
}
void Bio::setBio(const string& bio = "") {
    _bio = bio;
}
string Bio::print() const {
    return "";
}
string Bio::printHtml() const {
    return "";
}