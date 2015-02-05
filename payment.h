#ifndef PAYMENT_H
#define PAYMENT_H

#include <QDate>
#include "username.h"
#include "subscription.h"
#include "billmethod.h"

class Payment {
private:
    Username* _requester;
    Subscription* _sub;
    BillMethod* _bmethod;
    bool _approvation;
    QDate _appdate;
public:
    Payment(Username*, Subscription*, bool = false, const QDate& = QDate::currentDate());
    Payment(Username*, Subscription*, BillMethod*, bool = false, const QDate& = QDate::currentDate());
    Payment(const Payment&);
    ~Payment();
    Payment* clone() const;
    bool approvation() const;
    void setApprovation(bool);
    Subscription* subscription() const;
    void setSubscription(Subscription*);
    BillMethod* billMethod() const;
    void setBillMethod(BillMethod*);
    QDate appDate() const;
    void setAppDate(const QDate& = QDate::currentDate());
};
#endif