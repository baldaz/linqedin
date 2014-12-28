#ifndef SUBSCRIPTION_H
#define SUBSCRIPTION_H

#include "privlevel.h"
#include <string>

using std::string;

class Subscription {
private:
    string _paypal;
    privLevel _level;
    static double _basic;
    static double _business;
    static double _executive;
public:
    string paypal() const;
    void setPaypal(string);
    privLevel level() const;
    void setLevel(privLevel);
    static void setLevelAmount(privLevel, double);
    static double levelAmount(privLevel);
};
#endif