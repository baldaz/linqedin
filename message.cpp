#include "message.h"

Message::Message(const Username& sender, const Username& receiver, const string& obj, const string& body, bool read, const QDate& s, const QDate& r) :
    _sender(sender), _receiver(receiver), _object(obj), _body(body), _read(read), _sent(s), _recv(r) {}
Message* Message::clone() const {
    return new Message(*this);
}
bool Message::operator==(const Message& m) const {
    return ((_sender.login() == m._sender.login()) && (_receiver.login() == m._receiver.login())
            && (_object == m._object) && (_body == m._body) && (_read == m._read) && (_sent == m._sent) && (_recv == m._recv));
}
bool Message::isRead() const {
    return _read;
}
void Message::setRead(bool read) {
    _read = read;
}
Username Message::sender() const {
    return _sender;
}
Username Message::receiver() const {
    return _receiver;
}
string Message::object() const {
    return _object;
}
string Message::body() const {
    return _body;
}
QDate Message::sent() const {
    return _sent;
}
QDate Message::recv() const {
    return _recv;
}