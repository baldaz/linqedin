#ifndef SUBSCRIPTION_H
#define SUBSCRIPTION_H

#include "privlevel.h"
#include <string>

using std::string;

class Subscription {
private:
    string _paypal;
    privLevel _level;
public:
    string paypal() const;
    void setPaypal(string);
    privLevel level() const;
    void setLevel(privLevel);
};
#endif