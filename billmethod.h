#ifndef BILLMETHOD_H
#define BILLMETHOD_H

#include <string>

class BillMethod {
public:
    virtual std::string code() const =0;
    virtual std::string nominee() const =0;
};

class CreditCard : public BillMethod {
private:
    std::string _code;
    std::string _nominee;
public:
    CreditCard(std::string, std::string);
    virtual std::string code() const;
    virtual std::string nominee() const;
};
#endif