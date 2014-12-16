#include <iostream>
#include "account.h"
#include "linqnet.h"
#include "linqdb.h"

using std::cout;
using std::endl;

main() {
    LinqDB db; /*DB utenti*/
    LinqNet net; /*Rete amicizie*/
    LinqNet net2;
    LinqNet net3;
    Username usr("Andrea", "password");
    UserInfo uf("Andrea", "Baldan", "08-10-1988", "a.g.baldan@gmail.com", "3450515048");
    Username usr2("Pablos", "maurisio");
    UserInfo uf2("Pablos", "Escobar", "15-12-1923", "escobar@cartello.cb", "9873478233");
    Username usr3("Atos", "piovra");
    UserInfo uf3("Atos", "Bierta", "15-10-1973", "atos@bierta.es", "4872474213");
    Account acc(&uf, &usr);
    Account acc2(&uf2, &usr2);
    Account acc3(&uf3, &usr3);
    // cout << acc.getInfo()->getName() << endl;
    User* s3 = new BasicUser(&acc3, &net3);
    User* s2 = new BasicUser(&acc2, &net2);
    User* s = new BasicUser(&acc, &net);
    net.addUser(s2); /*inserisco pablo negli amici di andrea*/
    net.addUser(s3);
    net2.addUser(s3);
    net3.addUser(s2);
    db.addUser(s);
    db.addUser(s2);
    db.addUser(s3);
    cout<<endl;
    cout<<db;
    net.delUser(s3);
    cout << "Andrea >> " << net << endl;
    cout << "Pablos >> " << net2 << endl;
    cout << "Atos >> " << net3 << endl;
    cout<<endl;
    // SPUser sp(s);
    // db.addUser(sp);
    // cout<<db;
    // User s;
    // db.addUser(s);
}