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
    Username usr2("Pablo", "maurissio");
    UserInfo uf2("Pablo", "Escobar", "15-12-1923", "escobar@cartello.cb", "9873478233");
    Account acc(&uf, &usr);
    Account acc2(&uf2, &usr2);
    // cout << acc.getInfo()->getName() << endl;
    User s(&acc, 0);
    User s2(&acc2, 0);
    db.addUser(s);
    db.addUser(s2);
    cout<<db;
    // SPUser sp(s);
    // db.addUser(sp);
    // cout<<db;
    // User s;
    // db.addUser(s);
}