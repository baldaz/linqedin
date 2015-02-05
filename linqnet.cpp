#include "linqnet.h"
#include <sstream>

using std::cout;
using std::endl;

LinqNet::LinqNet() {}
LinqNet::LinqNet(const LinqNet& net) : _net(net._net) {}
LinqNet::~LinqNet() { _net.clear(); }
LinqNet* LinqNet::clone() const {
    return new LinqNet(*this);
}
int LinqNet::size() const {
    return _net.size();
}
void LinqNet::addUser(User* usr) throw(Error) {
    list<SmartPtr<User> >::iterator it = _net.begin();
    bool alreadyIn = false;
    for(; it != _net.end() && !alreadyIn; ++it) {
        if(((*it)->account()->username()) == (usr->account()->username()))
            alreadyIn = true;
    }
    if(!alreadyIn) _net.push_back(SmartPtr<User>(usr));
    else throw Error(dupLink, "Already connected with that user");
}
void LinqNet::removeUser(const Username& usr) throw(Error) {
    list<SmartPtr<User> >::iterator it = _net.begin();
    bool found = false;
    for(; it != _net.end() && !found; ++it)
        if(((*it)->account()->username().login()) == (usr.login())) {
            found = true;
            _net.erase(it);
        }
    if(!found) throw Error(userNotFound, "Connection not found");
}
vector<Username> LinqNet::username() const {
    vector<Username> us_list;
    list<SmartPtr<User> >::const_iterator it = _net.begin();
    for(; it != _net.end(); ++it){
        us_list.push_back((*it)->account()->username());
    }
    return us_list;
}
string LinqNet::printHtml() const {
    string html = "";
    std::ostringstream o;
    o << size();
    if(!_net.empty()) {
        UserInfo* uf = NULL;
        html += "<h4>Connections (" + o.str() + ")</h4><p style='font-weight:400'>";
        list<SmartPtr<User> >::const_iterator it = _net.begin();
        for(; it != _net.end(); ++it) {
            uf = dynamic_cast<UserInfo*> ((*it)->account()->info());
            html += uf->name() + " " + uf->surname() + " - ";
        }
        html += "</p>";
    }
    return html;
}
list<SmartPtr<User> >::const_iterator LinqNet::begin() const {
    return _net.begin();
}
list<SmartPtr<User> >::const_iterator LinqNet::end() const {
    return _net.end();
}
ostream& operator<<(ostream& os, const LinqNet& net) {
    if(!net.size()) { os << "Nessun amico per te" << endl; }
    else {
        list<SmartPtr<User> >::const_iterator it = net.begin();
        for(; it != net.end(); ++it)
            os << (*it)->account()->username().login() << " ";
    }
    return os;
}