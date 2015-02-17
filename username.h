#ifndef USERNAME_H
#define USERNAME_H

#include <string>

using std::string;

class Username {
private:
    string _login;
    string _password;
public:
    Username(const string& = "", const string& = "");
    // Username(const Username&);
    // Username* clone() const;
    const string& login() const;
    void setLogin(const string&);
    const string& password() const;
    void setPassword(const string&);
    bool operator==(const Username&) const;
    bool operator!=(const Username&) const;
};
#endif