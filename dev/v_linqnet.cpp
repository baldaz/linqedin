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
void LinqNet::addUser(User* usr) {
    vector<SmartPtr<User> >::iterator it = _net.begin();
    bool alreadyIn = false;
    for(; it < _net.end() && !alreadyIn; ++it) {
        if(*((*it)->account()->username()) == *(usr->account()->username()))
            alreadyIn = true;
    }
    if(!alreadyIn) _net.push_back(SmartPtr<User>(usr));
    else std::cout << "già collegato!" << std::endl;
}
void LinqNet::removeUser(const Username& usr) {
    vector<SmartPtr<User> >::iterator it = _net.begin();
    bool found = false;
    for(; it < _net.end() && !found; ++it)
        if(((*it)->account()->username().login()) == (usr.login())) {
            found = true;
            if(found) _net.erase(it);
        }
}
vector<SmartPtr<Username> > LinqNet::username() const {
    vector<SmartPtr<Username> > list;
    vector<SmartPtr<User> >::const_iterator it = _net.begin();
    for(; it < _net.end(); ++it){
        list.push_back(SmartPtr<Username>((*it)->account()->username()));
    }
    return list;
}
string LinqNet::printHtml() const {
    string html = "";
    std::ostringstream o;
    o << size();
    if(!_net.empty()) {
        UserInfo* uf = NULL;
        html += "<h4>Connections (" + o.str() + ")</h4><p style='font-weight:400'>";
        vector<SmartPtr<User> >::const_iterator it = _net.begin();
        for(; it < _net.end(); ++it) {
            uf = dynamic_cast<UserInfo*> ((*it)->account()->info());
            html += uf->name() + " " + uf->surname() + " - ";
        }
        html += "</p>";
    }
    return html;
}
SmartPtr<User> LinqNet::operator[](const int& i) const {
    return _net[i];
}
ostream& operator<<(ostream& os, const LinqNet& net) {
    if(!net.size()) { os << "Nessun amico per te" << endl; }
    else {
        for(int i = 0; i < net.size(); ++i)
            os << net[i]->account()->username().login() << " ";
    }
    return os;
}