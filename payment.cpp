#include "payment.h"

Payment::Payment(Username* user, Subscription* sub, BillMethod* bmthd, bool appr) : _requester(user->clone()), _sub(sub->clone()), _bmethod(bmthd->clone()), _approvation(appr) {}
Payment::Payment(const Payment& pay) : _requester(pay._requester->clone()), _approvation(pay._approvation), _sub(pay._sub->clone()), _bmethod(pay._bmethod->clone()) {}
Payment::~Payment() { delete _requester; delete _sub; delete _bmethod; }
Payment* Payment::clone() const {
    return new Payment(*this);
}
bool Payment::approvation() const {
    return _approvation;
}
void Payment::setApprovation(bool appr) {
    _approvation = appr;
}
Subscription* Payment::subscription() const {
    return _sub;
}
void Payment::setSubscription(Subscription* sub) {
    _sub = sub;
}
BillMethod* Payment::billMethod() const {
    return _bmethod;
}
void Payment::setBillMethod(BillMethod* bmethod) {
    _bmethod = bmethod;
}