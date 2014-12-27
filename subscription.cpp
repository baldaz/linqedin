#include "subscription.h"

string Subscription::paypal() const {
    return _paypal;
}
void Subscription::setPaypal(string pp) {
    _paypal = pp;
}
privLevel Subscription::level() const {
    return _level;
}
void Subscription::setLevel(privLevel newlevel) {
    _level = newlevel;
}