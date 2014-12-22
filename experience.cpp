#include "experience.h"

Experience::~Experience() {}
Instruction::Instruction() {}
Instruction::Instruction(QString l, QString f, QString t) : _location(l), _from(f), _to(t) {}
Experience* Instruction::clone() const {
    return new Instruction(*this);
}
QString Instruction::location() const {
    return _location;
}
QString Instruction::from() const {
    return _from;
}
QString Instruction::to() const {
    return _to;
}
void Instruction::setLocation(QString l = "") {
    _location = l;
}
void Instruction::setFrom(QString f = "") {
    _from = f;
}
void Instruction::setTo(QString t = "") {
    _to = t;
}
QString Instruction::print() const { return 0;}

Work::Work() : Instruction() {}
Work::Work(QString l, QString d, QString f, QString t) : Instruction(l, f, t), _description(d) {}
Experience* Work::clone() const {
    return new Work(*this);
}
QString Work::description() const {
    return _description;
}
void Work::setDescription(QString d = "") {
    _description = d;
}
QString Work::print() const { return 0; }