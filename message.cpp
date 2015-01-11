#include "message.h"

Message::Message(const Username& sender, const Username& receiver, const string& obj, const string& body, bool read) :
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
const string& Message::object() const {
    return _object;
}
void Message::setObject(const string& obj) {
    _object = obj;
}
const string& Message::body() const {
    return _body;
}
void Message::setBody(const string& body) {
    _body = body;
}