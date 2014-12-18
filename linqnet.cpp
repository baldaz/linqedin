#include "linqnet.h"

using std::cout;
using std::endl;

int LinqNet::size() const {
    return _net.size();
}
void LinqNet::addUser(User* usr) {
    SPUser spu(usr);
    _net.push_back(spu);
}
void LinqNet::delUser(User* usr) {
    for(int i = 0; i < this->size(); i++) {
        if(_net[i]->account()->username()->login() == usr->account()->username()->login())
            _net.erase(_net.begin() + i);
    }
}
SPUser LinqNet::operator[](const int& i) const {
    return _net[i];
}
ostream& operator<<(ostream& os, const LinqNet& net) {
    if(!net.size()) { os << "Nessun amico per te" << endl; }
    else {
        for(int i = 0; i < net.size(); ++i)
            os << net[i]->account()->username()->login().toStdString() << " ";
    }
    return os;
}