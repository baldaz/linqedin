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
    ~Payment();
    bool approvation() const;
    void setApprovation(bool);
    Subscription* sub() const;
    void setSub(Subscription*);
    BillMethod* billMethod() const;
    void setBillMethod(BillMethod*);
};
#endif