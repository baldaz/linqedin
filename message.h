#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include "username.h"

using std::string;

class Message {
private:
    Username* _sender;
    Username* _receiver;
    string _object, _body;
    bool _read;
public:
    Message(const Username&, const Username&, const string&, const string&, bool);
    ~Message();
    bool isRead() const;
    void setRead(bool);
    Username* sender() const;
    void setSender(const Username&);
    Username* receiver() const;
    void setReceiver(const Username&);
    const string& object() const;
    void setObject(const string&);
    const string& body() const;
    void setBody(const string&);
};
#endif