#include "billmethod.h"

CreditCard::CreditCard(std::string code, std::string nominee) : _code(code), _nominee(nominee) {}
CreditCard::CreditCard(const CreditCard& cr) : _code(cr._code), _nominee(cr._nominee) {}
BillMethod* CreditCard::clone() const {
    return new CreditCard(*this);
}
std::string CreditCard::code() const {
    return _code;
}
std::string CreditCard::nominee() const {
    return _nominee;
}