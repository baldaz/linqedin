#include "experience.h"
#include "error.h"

Experience::Experience(int t, const string& l, const string& r, const QDate& f, const QDate& to) : _type(t), _location(l), _role(r) {
        if(f > to) throw Error(date, "Experience dates cannot be negative (from date should be inferior of to date)");
        else {
            _from = f;
            _to = to;
        }
    }
Experience::Experience(const Experience& xp) : _type(xp._type), _location(xp._location), _role(xp._role), _from(xp._from), _to(xp._to) {}
Experience& Experience::operator=(const Experience& x) {
    if(this != &x) {
        _type = x._type;
        _location = x._location;
        _role = x._role;
        _from = x._from;
        _to = x._to;
    }
    return *this;
}
bool Experience::operator==(const Experience& e) const {
	return (_type == e._type) && (_location == e._location) && (_role == e._role) && (_from == e._from) && (_to == e._to);
}
int Experience::type() const {
    return _type;
}
void Experience::setType(int t) {
    _type = t;
}
string Experience::location() const {
    return _location;
}
void Experience::setLocation(const string & l) {
    _location = l;
}
string Experience::role() const {
    return _role;
}
void Experience::setRole(const string& r) {
    _role = r;
}
QDate Experience::from() const {
    return _from;
}
void Experience::setFrom(const QDate& f) {
    _from = f;
}
QDate Experience::to() const {
    return _to;
}
void Experience::setTo(const QDate& t) {
    _to = t;
}
