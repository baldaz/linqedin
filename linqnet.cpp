#include "linqnet.h"

using std::cout;
using std::endl;

LinqNet::~LinqNet() {}
LinqNet* LinqNet::clone() const {
    return new LinqNet(*this);
}
int LinqNet::size() const {
    return _net.size();
}
void LinqNet::addUser(User* usr) {
    vector<SmartPtr<User> >::iterator it = _net.begin();
    bool alreadyIn = false;
    // User* tmp;
    for(; it < _net.end() && !alreadyIn; ++it) {
        // tmp = dynamic_cast<User*> (&(**it));
        // if(tmp &&  *(tmp->account()->username()) == *(usr->account()->username()))
        if(*((*it)->account()->username()) == *(usr->account()->username()))
            alreadyIn = true;
    }
    if(!alreadyIn) _net.push_back(SmartPtr<User>(usr));
    else std::cout << "già collegato!" << std::endl;
}
void LinqNet::removeUser(Username* usr) {
    vector<SmartPtr<User> >::iterator it = _net.begin();
    bool found = false;
    for(; it < _net.end() && !found; ++it)
        if(((*it)->account()->username()->login()) == (usr->login()))
            found = true;
    if(found) _net.erase(it);
            // _net.erase(_net.begin() + i);
            // std::cout << "trovato" << std::endl;
}
vector<Username*> LinqNet::username() const {
    vector<Username*> list;
    for(int i = 0; i < size(); ++i)
        list.push_back(_net[i]->account()->username());
    return list;
}
SmartPtr<User> LinqNet::operator[](const int& i) const {
    return _net[i];
}
ostream& operator<<(ostream& os, const LinqNet& net) {
    if(!net.size()) { os << "Nessun amico per te" << endl; }
    else {
        for(int i = 0; i < net.size(); ++i)
            os << net[i]->account()->username()->login() << " ";
    }
    return os;
}