#ifndef USERINFO_H
#define USERINFO_H

#include <QString>
#include <vector>
#include "experience.h"

using std::vector;

class Info {
public:
    virtual ~Info();
    // virtual Info* clone() const =0;
    virtual QString print() const =0;
};

class UserInfo : public Info {
private:
    bool _sex;
    QString _name, _surname, _birthdate, _email, _address, _telephon;
    vector<QString> _skills;
    vector<Experience*> _formations;
    vector<Experience*> _exps;
public:
    UserInfo();
    UserInfo(bool, QString, QString, QString, QString, QString, QString);
    // UserInfo(const UserInfo&);
    // Info* clone() const;
    // virtual ~UserInfo();
    UserInfo& operator=(const UserInfo&);
    QString name() const;
    QString surname() const;
    QString birthdate() const;
    QString email() const;
    QString address() const;
    QString telephon() const;
    bool sex() const;
    vector<QString> skills() const;
    vector<Experience*> experience() const;
    vector<Experience*> formations() const;
    void setSex(bool);
    void setName(QString);
    void setSurname(QString);
    void setBirthdate(QString);
    void setEmail(QString);
    void setAddress(QString);
    void setTelephon(QString);
    void addSkill(QString);
    void addExperience(Experience*);
    void addFormation(Experience*);
    virtual QString print() const;
};

#endif