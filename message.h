#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>

using std::string;

class Message {
private:
    Username* _sender, _receiver;
    string _object, _body;
    bool _read;
public:
    Message(Username*, Username*, string, string, bool);
    ~Message();
    bool isRead() const;
    void setRead(bool);
    Username* sender() const;
    void setSender(Username*);
    Username* receiver() const;
    void setReceiver(Username*);
    string object() const;
    void setObject(string);
    string body() const;
    void setBody(string);
};
#endif