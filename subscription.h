#ifndef SUBSCRIPTION_H
#define SUBSCRIPTION_H

#include "privlevel.h"
#include <string>

using std::string;

class Subscription {
private:
    privLevel _level;
    static double _basic;
    static double _business;
    static double _executive;
public:
    privLevel level() const;
    void setLevel(privLevel);
    static void setLevelAmount(privLevel, double);
    static double levelAmount(privLevel);
};
#endif