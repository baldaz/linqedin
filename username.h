#ifndef USERNAME_H
#define USERNAME_H

#include <string>

using std::string;

class Username {
private:
    string login;
    string password;
public:
    Username(string, string);
    string getLogin() const;
    string getPassword() const;
    void setLogin(string);
    void setPassword(string);
};
#endif