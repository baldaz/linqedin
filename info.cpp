#include "info.h"

Info::~Info() {}
UserInfo::UserInfo(const string& n, const string& s, const string& e, const string& a, const string& t, const string& w, const QDate& b) :
                _name(n), _surname(s), _email(e), _address(a), _telephon(t), _website(w), _birthdate(b){}
UserInfo::UserInfo(const UserInfo& uf) : _name(uf._name), _surname(uf._surname), _email(uf._email), _address(uf._address),
                _telephon(uf._telephon), _website(uf._website), _birthdate(uf._birthdate), _languages(uf._languages),
                _skills(uf._skills), _interests(uf._interests) {
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
        _skills = uif._skills;
        _exp = uif._exp;
        _interests = uif._interests;
        _languages = uif._languages;
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
void UserInfo::setName(const string& n = "") {
    _name = n;
}
void UserInfo::setSurname(const string& s = "") {
    _surname = s;
}
void UserInfo::setBirthdate(const QDate& b ) {
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
void UserInfo::addInterest(const string& newinterest = "") {
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
int UserInfo::age() const {
    QDate today = QDate::currentDate();
    int age = today.toJulianDay() - _birthdate.toJulianDay();
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
string UserInfo::printHtml() const {
    std::ostringstream o;
    o << age();
    string html = "";
    html = "<html><body>";
    html += "<h2>" + _name + " " + _surname + "</h2>";
    html += "<p style='font-weight: 400; font-size:14px;'> " + o.str() + " years old<br>";
    html += _address + "</p>";
    html += "<h4><img src='img/rugby100.png'>  Interests</h4><p style='font-weight: 400; font-size:14px;line-height:26px'>";
    vector<string>::const_iterator it;
    if(!_interests.empty()) {
        it = _interests.begin();
        for(; it < _interests.end(); ++it)
            html += "<span style='background-color:rgba(102,102,156,.5);'>&nbsp;" + *it + "&nbsp;</span>&nbsp;&nbsp;";
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
    if(!_exp.empty()) {
        html += "<h4><img src='img/graduate34.png'>  Educations</h4><p style='font-weight: 400; font-size:14px;'>";
        list<Experience*>::const_iterator itr = _exp.begin();
        string jobs = "";
        bool job = false;
        for(; itr != _exp.end(); ++itr) {
            if((*itr)->type() == 0)
                if(itr == _exp.end())
                    html += (*itr)->role() + " at " + (*itr)->location() + " from " + (*itr)->from().toString("dd.MM.yyyy").toStdString() + " to " + (*itr)->to().toString("dd.MM.yyyy").toStdString();
                else
                    html += (*itr)->role() + " at " + (*itr)->location() + " from " + (*itr)->from().toString("dd.MM.yyyy").toStdString() + " to " + (*itr)->to().toString("dd.MM.yyyy").toStdString() + "<br>";
            else if((*itr)->type() == 1) {
                job = true;
                if(itr == _exp.end())
                    jobs += (*itr)->role() + " at " + (*itr)->location() + " from " + (*itr)->from().toString("dd.MM.yyyy").toStdString() + " to " + (*itr)->to().toString("dd.MM.yyyy").toStdString();
                else
                    jobs += (*itr)->role() + " at " + (*itr)->location() + " from " + (*itr)->from().toString("dd.MM.yyyy").toStdString() + " to " + (*itr)->to().toString("dd.MM.yyyy").toStdString() + "<br>";
            }
        }
        if(job) {
            html += "<h4><img src='img/work3.png'>  Job Experiences</h4><p style='font-weight: 400; font-size:14px;'>";
            html += jobs;
        }
    }
    html += "</p>";
    html += "<h4><img src='img/business133.png'>  Contacts</h4><p style='font-weight: 400; font-size:14px'>" + _email + " &nbsp;&nbsp;<a style='color:#4782EC;' href='#'>" + _website + "</a><br> Telephon  " + _telephon + "</p>";
    return html;
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
void Bio::setBio(const string& bio = "") {
    _bio = bio;
}
string Bio::print() const {
    return "";
}
string Bio::printHtml() const {
    string html = UserInfo::printHtml();
    if(!_bio.empty()) {
        html += "<h4><img src='img/user91.png'> Short Biography</h4>";
        html += "<p style='font-weight:400'>" + bio() + "</p>";
    }
    return html;
}
