#ifndef USERNAME_H
#define USERNAME_H

#include <QString>

class Username {
private:
    QString _login;
    QString _password;
public:
    Username(QString, QString);
    QString login() const;
    void setLogin(QString);
    QString password() const;
    void setPassword(QString);
    bool operator==(const Username&) const;
};
#endif