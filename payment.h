#ifndef PAYMENT_H
#define PAYMENT_H

#include "username.h"
#include "subscription.h"

class Payment {
private:
    Username* _requester;
    bool _approvation;
    Subscription* _sub;
public:
    Payment(Username*, bool);
    ~Payment();
    bool approvation() const;
    void setApprovation(bool);
    Subscription* sub() const;
    void setSub(Subscription*);
};
#endif