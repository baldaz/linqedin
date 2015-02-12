#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <QDate>
#include "username.h"

using std::string;

class Message {
private:
    Username _sender;
    Username _receiver;
    string _object, _body;
    bool _read;
    QDate _sent, _recv;
public:
    Message(const Username&, const Username&, const string&, const string&, bool, const QDate& = QDate::currentDate(), const QDate& = QDate::currentDate());
    Message* clone() const;
    bool operator==(const Message&) const;
    bool isRead() const;
    void setRead(bool);
    Username sender() const;
    Username receiver() const;
    string object() const;
    string body() const;
    QDate sent() const;
    QDate recv() const;
};
#endif