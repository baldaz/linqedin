#ifndef PAYMENT_H
#define PAYMENT_H

#include "username.h"
#include "subscription.h"
#include "billmethod.h"

class Payment {
private:
    Username* _requester;
    bool _approvation;
    Subscription* _sub;
    BillMethod* _bmethod;
public:
    Payment(Username*, bool);
    Payment(const Payment&);
    ~Payment();
    Payment* clone() const;
    bool approvation() const;
    void setApprovation(bool);
    Subscription* subscription() const;
    void setSubscription(Subscription*);
    BillMethod* billMethod() const;
    void setBillMethod(BillMethod*);
};
#endif