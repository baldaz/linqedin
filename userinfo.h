#ifndef USERINFO_H
#define USERINFO_H

class UserInfo {
private:
    string _name;
    string _surname;
    string _birthdate;
    string _email;
    string _telephon;
public:
    string getName() const;
    string getSurname() const;
    string getBirthdate() const;
    string getEmail() const;
    string getTelephon() const;
    void setName(string);
    void setSurname(string);
    void setBirthdate(string);
    void setEmail(string);
    void setTelephon(string);
};
#endif