#ifndef USERNAME_H
#define USERNAME_H

#include <string>

using std::string;

class Username {
private:
    string _login;
    string _password;
public:
    Username(string, string);
    string login() const;
    void setLogin(string);
    string password() const;
    void setPassword(string);
    bool operator==(const Username&) const;
};
#endif