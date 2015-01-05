#include "billmethod.h"

CreditCard::CreditCard(std::string code, std::string nominee) : _code(code), _nominee(nominee) {}
std::string CreditCard::code() const {
    return _code;
}
std::string CreditCard::nominee() const {
    return _nominee;
}