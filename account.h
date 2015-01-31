#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <vector>
#include "avatar.h"
#include "username.h"
#include "info.h"
#include "privlevel.h"
#include "payment.h"

class Account {
private:
    Info* _info;
    Username _user;
    privLevel _privilege;
    vector<SmartPtr<Payment> > _history;
    Avatar _avatar;
public:
    // Account();
    Account(Info*, const Username&, privLevel);
    Account(const Account&);
    ~Account();
    Account* clone() const;
    Account& operator=(const Account&);
    Username username() const;
    Info* info() const;
    privLevel prLevel() const;
    Avatar avatar() const;
    void setAvatar(const Avatar&);
    void setInfo(Info*);
    void setPrLevel(privLevel);
    vector<SmartPtr<Payment> > history() const;
    SmartPtr<Payment> lastPayment() const;
    void addPayment(const Payment&);
};
#endif