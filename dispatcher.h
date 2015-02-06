#ifndef DISPATCHER_H
#define DISPATCHER_H

#include <string>

using std::string;

class Info;
class UserInfo;
class Bio;

class Dispatcher {
public:
    virtual ~Dispatcher();
    virtual string dispatch(const UserInfo&) const = 0;
    virtual string dispatch(const Bio&) const = 0;
};

class DispatcherHtml : public Dispatcher{
public:
    virtual string dispatch(const UserInfo&) const;
    virtual string dispatch(const Bio&) const;
};

#endif