#include "subscription.h"

double Subscription::_basic = 0;
double Subscription::_business = 14.90;
double Subscription::_executive = 29.90;

Subscription::Subscription(privLevel lev) : _level(lev) {}
//Subscription::Subscription(const Subscription& sub) : _level(sub._level) {}
Subscription* Subscription::clone() const {
    return new Subscription(*this);
}
privLevel Subscription::level() const {
    return _level;
}
void Subscription::setLevel(privLevel newlevel) {
    _level = newlevel;
}
void Subscription::setLevelAmount(privLevel level, double amount) {
    switch(level) {
        case basic:
            _basic = amount;
        break;
        case business:
            _business = amount;
        break;
        case executive:
            _executive = amount;
        break;
    }
}
double Subscription::levelAmount(privLevel level) {
    switch(level) {
        case basic:
            return _basic;
        break;
        case business:
            return _business;
        break;
        case executive:
            return _executive;
        break;
        default:
            return 0;
        break;
    }
}