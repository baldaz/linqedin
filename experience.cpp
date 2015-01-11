#include "experience.h"

Experience::~Experience() {}
Instruction::Instruction() {}
Instruction::Instruction(const string& l, const string& f, const string& t) : _location(l), _from(f), _to(t) {}
Instruction::Instruction(const Instruction& ins) : _location(ins._location), _from(ins._from), _to(ins._to) {}
Experience* Instruction::clone() const {
    return new Instruction(*this);
}
const string& Instruction::location() const {
    return _location;
}
const string& Instruction::from() const {
    return _from;
}
const string& Instruction::to() const {
    return _to;
}
void Instruction::setLocation(const string& l = "") {
    _location = l;
}
void Instruction::setFrom(const string& f = "") {
    _from = f;
}
void Instruction::setTo(const string& t = "") {
    _to = t;
}
string Instruction::print() const { return 0;}

Work::Work() : Instruction() {}
Work::Work(const string& l, const string& d, const string& f, const string& t) : Instruction(l, f, t), _description(d) {}
Work::Work(const Work& wrk) : Instruction(wrk), _description(wrk._description) {}
Experience* Work::clone() const {
    return new Work(*this);
}
const string& Work::description() const {
    return _description;
}
void Work::setDescription(const string& d = "") {
    _description = d;
}
string Work::print() const { return 0; }