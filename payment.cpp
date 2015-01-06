#include "payment.h"

Payment::Payment(Username* user, bool appr = false) : _requester(user), _approvation(appr) {}
Payment::~Payment() { delete _requester; delete _sub; }
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