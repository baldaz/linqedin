#include "linqnet.h"

using std::cout;
using std::endl;

int LinqNet::getSize() const {
    return _net.size();
}
void LinqNet::addUser(User* usr) {
    SPUser spu(usr);
    _net.push_back(spu);
}
void LinqNet::delUser(User* usr) {
    for(int i = 0; i < this->getSize(); i++) {
        if(_net[i]->getUsername()->getLogin() == usr->getUsername()->getLogin())
            _net.erase(_net.begin() + i);
    }
}
SPUser LinqNet::operator[](const int& i) const {
    return _net[i];
}
ostream& operator<<(ostream& os, const LinqNet& net) {
    if(!net.getSize()) { os << "Nessun amico per te" << endl; }
    else {
        for(int i = 0; i < net.getSize(); ++i)
            os << net[i]->getUsername()->getLogin() << " ";
    }
    return os;
}