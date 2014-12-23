#include "linqnet.h"

using std::cout;
using std::endl;

LinqNet::~LinqNet() {}
LinqNet* LinqNet::clone() const {
    return new LinqNet(*this);
}
bool LinqNet::isPresent(Username* user) const {

}
int LinqNet::size() const {
    return _net.size();
}
void LinqNet::addUser(User* usr) {
    SPUser spu(usr);
    _net.push_back(spu);
}
void LinqNet::removeUser(Username* usr) {
    for(int i = 0; i < size(); i++)
        if((_net[i]->account()->username()->login()) == usr->login())
            _net.erase(_net.begin() + i);
            // std::cout << "trovato" << std::endl;
}
vector<Username*> LinqNet::username() const {
    vector<Username*> list;
    for(int i = 0; i < size(); ++i)
        list.push_back(_net[i]->account()->username());
    return list;
}
SPUser LinqNet::operator[](const int& i) const {
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