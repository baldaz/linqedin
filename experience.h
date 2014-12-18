#ifndef EXPERIENCE_H
#define EXPERIENCE_H

#include <QString>

class Experience {
public:
    virtual ~Experience();
    virtual QString print() const =0;
};

class Instruction : public Experience {
protected:
    QString _location, _from, _to;
public:
    Instruction();
    Instruction(QString, QString, QString);
    // ~Instruction();
    QString location() const;
    QString from() const;
    QString to() const;
    void setLocation(QString);
    void setFrom(QString);
    void setTo(QString);
    virtual QString print() const;
};

class Work : public Instruction {
protected:
    QString _description;
public:
    Work();
    Work(QString, QString, QString, QString);
    // ~Work();
    QString description() const;
    void setDescription(QString);
    virtual QString print() const;
};

#endif