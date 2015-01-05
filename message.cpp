#include "message.h"

Message::Message(const Username& sender, const Username& receiver, string obj, string body, bool read) :
    _sender(const_cast<Username*> (&sender)), _receiver(const_cast<Username*> (&receiver)), _object(obj), _body(body), _read(read) {}
Message::~Message() { delete _sender; delete _receiver; }
bool Message::isRead() const {
    return _read;
}
void Message::setRead(bool read) {
    _read = read;
}
Username* Message::sender() const {
    return _sender;
}
void Message::setSender(const Username& sender) {
    _sender = const_cast<Username*> (&sender);
}
Username* Message::receiver() const {
    return _receiver;
}
void Message::setReceiver(const Username& receiver) {
    _receiver = const_cast<Username*> (&receiver);
}
string Message::object() const {
    return _object;
}
void Message::setObject(string obj) {
    _object = obj;
}
string Message::body() const {
    return _body;
}
void Message::setBody(string body) {
    _body = body;
}