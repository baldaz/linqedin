#ifndef PAYMENT_H
#define PAYMENT_H

#include "username.h"
#include "privlevel.h"

class Payment {
private:
    Username* _requester;
    bool _approvation;
    privLevel _level;
public:
    Payment(Username*);
    ~Payment();
    bool approvation() const;
    void setApprovation(bool);
    privLevel level() const;
    void setLevel();
};
#endif