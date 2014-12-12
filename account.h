#ifndef ACCOUNT_H
#define ACCOUNT_H

class Info;

class Account {
public:
    void alterAccount();
    Info* displayProfile() const;
};
#endif