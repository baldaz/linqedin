#include "ads.h"
#include "username.h"

Ads::Ads(const string& t, const string& d) : _title(t), _description(d) {}
// Ads::Ads(const Ads& a) : _title(a._title), _description(a._description) {}
string Ads::title() const {
    return _title;
}
string Ads::description() const {
    return _description;
}
list<Username*> Ads::candidates() const {
    return _candidates;
}
bool Ads::operator==(const Ads& a) const {
    return (_title == a._title) && (_description == a._description);
}
void Ads::addCandidate(const Username& u) {
    bool found = false;
    for(list<Username*>::iterator it = _candidates.begin(); it != _candidates.end() && !found; ++it)
        if((*it)->login() == u.login()) found = true;
    if(!found) _candidates.push_back(const_cast<Username*> (&u));
}