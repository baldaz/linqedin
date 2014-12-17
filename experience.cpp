#include "experience.h"

using std::string;

Instruction::Instruction() {}
Instruction::Instruction(string l, string f, string t) : _location(l), _from(f), _to(t) {}
string Instruction::getLocation() const {
    return _location;
}
string Instruction::getFrom() const {
    return _from;
}
string Instruction::getTo() const {
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
string Instruction::print() const {}

Work::Work() : Instruction() {}
Work::Work(string l, string d, string f, string t) : Instruction(s, f, t), _description(d) {}
string Work::getDescription() const {
    return _description;
}
void Work::setDescription(string d = "") {
    _description = d;
}
string Work::print() const {}