#ifndef ERROR_H
#define ERROR_H

#include <string>

enum eType{IO, permission, dupUser, userNotFound, payment, dupGroup, groupNotFound, dupLink, date, missingField, mail};

class Error {
private:
    eType _type;
    std::string _message;
public:
    Error(eType t, const string& m = "") : _type(t), _message(m) {}
    eType errorType() const {
        return _type;
    }
    string errorMessage() const {
        return _message;
    }
};
#endif