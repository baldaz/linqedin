#include "experience.h"

Experience::~Experience() {}
Instruction::Instruction() {}
Instruction::Instruction(string l, string f, string t) : _location(l), _from(f), _to(t) {}
Instruction::Instruction(const Instruction& ins) : _location(ins._location), _from(ins._from), _to(ins._to) {}
Experience* Instruction::clone() const {
    return new Instruction(*this);
}
string Instruction::location() const {
    return _location;
}
string Instruction::from() const {
    return _from;
}
string Instruction::to() const {
    return _to;
}
void Instruction::setLocation(string l = "") {
    _location = l;
}
void Instruction::setFrom(string f = "") {
    _from = f;
}
void Instruction::setTo(string t = "") {
    _to = t;
}
string Instruction::print() const { return 0;}

Work::Work() : Instruction() {}
Work::Work(string l, string d, string f, string t) : Instruction(l, f, t), _description(d) {}
Work::Work(const Work& wrk) : Instruction(wrk), _description(wrk._description) {}
Experience* Work::clone() const {
    return new Work(*this);
}
string Work::description() const {
    return _description;
}
void Work::setDescription(string d = "") {
    _description = d;
}
string Work::print() const { return 0; }