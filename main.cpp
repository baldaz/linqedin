#include <iostream>
#include "account.h"
#include "linqnet.h"
#include "linqdb.h"

using std::cout;
using std::endl;

main() {
    LinqDB db; /*DB utenti*/
    LinqNet net; /*Rete amicizie*/
    Username usr("Andrea", "password");
    UserInfo uf("Andrea", "Baldan", "08-10-1988", "a.g.baldan@gmail.com", "3450515048");
    Username usr2("Pablos", "maurisio");
    UserInfo uf2("Pablos", "Escobar", "15-12-1923", "escobar@cartello.cb", "9873478233");
    Account acc(&uf, &usr);
    Account acc2(&uf2, &usr2);
    // cout << acc.getInfo()->getName() << endl;
    User s2(&acc2, 0);
    net.addUser(s2); /*inserisco pablo negli amici di andrea*/
    User s(&acc, &net);
    db.addUser(s);
    db.addUser(s2);
    cout<<endl;
    cout<<db;
    cout << "Andrea amico di " << net;
    cout<<endl;
    // SPUser sp(s);
    // db.addUser(sp);
    // cout<<db;
    // User s;
    // db.addUser(s);
}