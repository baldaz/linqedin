#include "linqnet.h"

using std::cout;
using std::endl;

void LinqNet::addUser(const User& usr) {
    SPUser spu(new User(usr));
    _net.push_back(spu);
}
int LinqNet::getSize() const {
    return _net.size();
}
SPUser LinqNet::operator[](const int& i) const {
    return _net[i];
}
ostream& operator<<(ostream& os, const LinqNet& net) {
    if(!net.getSize()) { os << "Nessun amico per te" << endl; }
    else {
        for(int i = 0; i < net.getSize(); ++i){
            os << net[i]->getUsername()->getLogin() << endl;
        }
    }
    return os;
}