#include "payment.h"

Payment::Payment(Username* user, bool appr = false) : _requester(user), _approvation(appr) {}
Payment::~Payment() { delete _requester; }
bool Payment::approvation() const {
    return _approvation;
}
void Payment::setApprovation(bool appr) {
    _approvation = appr;
}
Subscription* Payment::sub() const {
    return _sub;
}
void Payment::setSub(Subscription* sub) {
    _sub = sub;
}