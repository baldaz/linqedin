#include "experience.h"

Experience::Experience(int t, const string& l, const string& r, const QDate& f, const QDate& to)
    : _type(t), _location(l), _role(r), _from(f), _to(to) {}
// Experience::Experience(const Experience& xp) : _type(xp._type), _location(xp._location), _role(xp._role), _from(xp._from), _to(xp._to) {}
// Experience& Experience::operator=(const Experience& x) {
//     if(this != &x) {
//         _type = x._type;
//         _location = x._location;
//         _role = x._role;
//         _from = QDate(_from.day(), _from.month(), _from.year());
//         _to = QDate(_to.day(), _to.month(), _to.year());
//     }
//     return *this;
// }
bool Experience::operator==(const Experience& e) const {
	return _type == e._type
		&& _location == e._location
		&& _role == e._role
		&& _from == e._from
		&& _to == e._to ;
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
// Experience::~Experience() {}
// Instruction::Instruction() {}
// Instruction::Instruction(const string& l, const string& f, const string& t) : _location(l), _from(f), _to(t) {}
// Instruction::Instruction(const Instruction& ins) : _location(ins._location), _from(ins._from), _to(ins._to) {}
// Experience* Instruction::clone() const {
//     return new Instruction(*this);
// }
// const string& Instruction::location() const {
//     return _location;
// }
// const string& Instruction::from() const {
//     return _from;
// }
// const string& Instruction::to() const {
//     return _to;
// }
// void Instruction::setLocation(const string& l = "") {
//     _location = l;
// }
// void Instruction::setFrom(const string& f = "") {
//     _from = f;
// }
// void Instruction::setTo(const string& t = "") {
//     _to = t;
// }
// string Instruction::print() const { return 0;}

// Work::Work() : Instruction() {}
// Work::Work(const string& l, const string& d, const string& f, const string& t) : Instruction(l, f, t), _description(d) {}
// Work::Work(const Work& wrk) : Instruction(wrk), _description(wrk._description) {}
// Experience* Work::clone() const {
//     return new Work(*this);
// }
// const string& Work::description() const {
//     return _description;
// }
// void Work::setDescription(const string& d = "") {
//     _description = d;
// }
// string Work::print() const { return 0; }
